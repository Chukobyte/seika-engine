#ifndef PYTHON_SCRIPT_CONTEXT_H
#define PYTHON_SCRIPT_CONTEXT_H

#include <map>

#include "../script_context.h"
#include "python_cache.h"

class PythonScriptContext : public ScriptContext {
  private:
    CPyInstance *pyInstance = nullptr;
    PythonCache *pythonCache = nullptr;
    std::map<Entity, CPyObject> activeClassInstances;
//    std::map<Entity, int> instanceScriptFunctionFlags;
    CPyObject startFunctionName;
    CPyObject physicsProcessFunctionName;
    CPyObject endFunctionName;
    ComponentManager *componentManager = nullptr;
  public:
    ~PythonScriptContext() {
        delete pyInstance;
    }

    void Initialize() override {
        pyInstance = new CPyInstance();
        pythonCache = new PythonCache();
        startFunctionName = PyUnicode_FromString("_start");
        physicsProcessFunctionName = PyUnicode_FromString("_physics_process");
        endFunctionName = PyUnicode_FromString("_end");
        componentManager = GD::GetContainer()->componentManager;
    }

    void CreateEntityInstance(Entity entity) override {
        ScriptableClassComponent scriptableClassComponent = componentManager->GetComponent<ScriptableClassComponent>(entity);

        // Create Instance
        CPyObject pClass = pythonCache->GetClassObject(scriptableClassComponent.classPath, scriptableClassComponent.className);
        // Instance
        CPyObject argList = Py_BuildValue("(i)", entity);
        CPyObject pClassInstance = PyObject_CallObject(pClass, argList);
        assert(pClassInstance != nullptr && "Python class instance is NULL on creation!");
        pClassInstance.AddRef();
        pClassInstance.AddRef();
        activeClassInstances.emplace(entity, pClassInstance);

        // Call Start
        if (PyObject_HasAttr(pClassInstance, startFunctionName)) {
            PyObject_CallMethod(activeClassInstances[entity], "_start", nullptr);
        }
    }

    void DeleteEntityInstance(Entity entity) override {
        if (activeClassInstances.count(entity) > 0) {
            CPyObject classInstance = activeClassInstances[entity];
            if (PyObject_HasAttr(classInstance, endFunctionName)) {
                PyObject_CallMethod(classInstance, "_end", nullptr);
                classInstance.Release();
                activeClassInstances.erase(entity);
            }
        }
    }

    void PhysicsProcess(Entity entity, double deltaTime) override {
        assert(activeClassInstances.count(entity) > 0 && "Entity not registered to python script context!");
        if (PyObject_HasAttr(activeClassInstances[entity], physicsProcessFunctionName)) {
            CPyObject processCallValue = PyObject_CallMethod(activeClassInstances[entity], "_physics_process", "(f)", deltaTime);
        }
        PyErr_Print();
    }

    void ReceiveSubscribedSignal(Entity subscriberEntity, const std::string &subscriberFunctionName, SignalArguments args) override {}

    void Destroy() override {}
};

#endif //PYTHON_SCRIPT_CONTEXT_H
