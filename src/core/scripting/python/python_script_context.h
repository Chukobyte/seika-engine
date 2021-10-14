#ifndef PYTHON_SCRIPT_CONTEXT_H
#define PYTHON_SCRIPT_CONTEXT_H

#include <map>

#include "../script_context.h"
#include "python_cache.h"

class PythonScriptContext : public ScriptContext {
  private:
    CPyInstance *pyInstance = nullptr;
    PythonCache *pythonCache = nullptr;
    CPyObject startFunctionName;
    CPyObject physicsProcessFunctionName;
    CPyObject endFunctionName;
    ComponentManager *componentManager = nullptr;
  public:
    ~PythonScriptContext() override {
        delete pyInstance;
    }

    void Initialize() override {
        pyInstance = new CPyInstance();
        pythonCache = PythonCache::GetInstance();
        startFunctionName = PyUnicode_FromString("_start");
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

    void Destroy() override {}
};

#endif //PYTHON_SCRIPT_CONTEXT_H
