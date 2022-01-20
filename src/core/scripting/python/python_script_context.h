#pragma once

#include <map>

#include "../script_context.h"
#include "python_cache.h"
#include "../../ecs/component/components/scriptable_class_component.h"

class PythonScriptContext : public ScriptContext {
  private:
    CPyInstance *pyInstance = nullptr;
    PythonCache *pythonCache = nullptr;
    CPyObject startFunctionName;
    CPyObject processFunctionName;
    CPyObject physicsProcessFunctionName;
    CPyObject endFunctionName;
    ComponentManager *componentManager = nullptr;

  public:
    ~PythonScriptContext() override {
        delete pyInstance;
    }

    void Initialize() override {
        pyInstance = new CPyInstance();
        ProjectProperties *projectProperties = ProjectProperties::GetInstance();
        if (projectProperties->IsAssetsInMemory()) {
            const std::string &archivePathInsertCommand = "sys.path.insert(0, '" + projectProperties->assetArchivePath + "')";
            Logger::GetInstance()->Debug("Adding archive to path with command:\n" + archivePathInsertCommand);
            PyRun_SimpleString(archivePathInsertCommand.c_str());
        }

        pythonCache = PythonCache::GetInstance();
        startFunctionName = PyUnicode_FromString("_start");
        processFunctionName = PyUnicode_FromString("_process");
        physicsProcessFunctionName = PyUnicode_FromString("_physics_process");
        endFunctionName = PyUnicode_FromString("_end");
        componentManager = GD::GetContainer()->componentManager;
    }

    void CreateEntityInstance(const Entity entity) override {
        ScriptableClassComponent scriptableClassComponent = componentManager->GetComponent<ScriptableClassComponent>(entity);
        pythonCache->CreateClassInstance(scriptableClassComponent.classPath, scriptableClassComponent.className, entity);
    }

    void CallStartOnEntityInstance(const Entity entity) override {
        if (PyObject_HasAttr(pythonCache->GetClassInstance(entity), startFunctionName)) {
            PyObject_CallMethod(pythonCache->GetClassInstance(entity), "_start", nullptr);
            PyErr_Print();
        }
    }

    void DeleteEntityInstance(const Entity entity) override {
        if (pythonCache->HasActiveInstance(entity)) {
            if (PyObject_HasAttr(pythonCache->GetClassInstance(entity), endFunctionName)) {
                PyObject_CallMethod(pythonCache->GetClassInstance(entity), "_end", nullptr);
            }

            pythonCache->RemoveClassInstance(entity);
        }
    }

    void Process(const Entity entity, const double deltaTime) override {
        PyGILState_STATE pyGilStateState = PyGILState_Ensure();
        {
            if (PyObject_HasAttr(pythonCache->GetClassInstance(entity), processFunctionName)) {
                CPyObject processCallValue = PyObject_CallMethod(pythonCache->GetClassInstance(entity), "_process", "(f)", deltaTime);
            }
        }
        PyGILState_Release(pyGilStateState);
        PyErr_Print();
    }

    void PhysicsProcess(const Entity entity, const double deltaTime) override {
        PyGILState_STATE pyGilStateState = PyGILState_Ensure();
        {
            if (PyObject_HasAttr(pythonCache->GetClassInstance(entity), physicsProcessFunctionName)) {
                CPyObject processCallValue = PyObject_CallMethod(pythonCache->GetClassInstance(entity), "_physics_process", "(f)", deltaTime);
            }
        }
        PyGILState_Release(pyGilStateState);
        PyErr_Print();
    }

    void FlushStdOutBuffer() override {
        PyRun_SimpleString("sys.stdout.flush()");
    }

    void ReceiveSubscribedSignal(const Entity subscriberEntity, const std::string &subscriberFunctionName, const SignalArguments args) override {
        PyObject *pyArgs = args.pyArgs;
        if (!pyArgs) {
            pyArgs = Py_BuildValue("[]");
        }
        CPyObject processCallValue = PyObject_CallMethod(pythonCache->GetClassInstance(subscriberEntity), subscriberFunctionName.c_str(), "O", pyArgs);
    }

    bool EntityHasProcessFunction(Entity entity) override {
        if (pythonCache->HasActiveInstance(entity) && PyObject_HasAttr(pythonCache->GetClassInstance(entity), processFunctionName)) {
            return true;
        }
        return false;
    }

    bool EntityHasPhysicsProcessFunction(Entity entity) override {
        if (pythonCache->HasActiveInstance(entity) && PyObject_HasAttr(pythonCache->GetClassInstance(entity), physicsProcessFunctionName)) {
            return true;
        }
        return false;
    }

    void Destroy() override {}
};
