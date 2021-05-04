#ifndef PYTHON_SCRIPT_CONTEXT_H
#define PYTHON_SCRIPT_CONTEXT_H

#include <map>

#include "../script_context.h"
#include "pyhelper.hpp"

class PythonScriptContext : public ScriptContext {
  private:
    CPyInstance *pyInstance = nullptr;
    std::map<Entity, CPyObject> activeClassInstances;
    std::map<Entity, int> instanceScriptFunctionFlags;
    CPyObject startFunctionName;
    CPyObject physicsProcessFunctionName;
    CPyObject endFunctionName;
    ComponentManager *componentManager = nullptr;

    CPyObject ExtractClassInstanceFromEntity(Entity entity) {
        ScriptableClassComponent scriptableClassComponent = componentManager->GetComponent<ScriptableClassComponent>(entity);
        // Import Module
        CPyObject pName = PyUnicode_FromString(scriptableClassComponent.classPath.c_str());
        CPyObject pModule = PyImport_Import(pName);
        assert(pModule != nullptr && "Python module is NULL!");

        // Class
        CPyObject pModuleDict = PyModule_GetDict(pModule);
        CPyObject pClass = PyDict_GetItemString(pModuleDict, scriptableClassComponent.className.c_str());
        assert(pClass != nullptr && "Python class is NULL!");

        // Instance
        CPyObject argList = Py_BuildValue("(i)", entity);
        CPyObject pClassInstance = PyObject_CallObject(pClass, argList);

        return pClassInstance;
    }
  public:
    ~PythonScriptContext() {
        delete pyInstance;
    }

    void Initialize() override {
        pyInstance = new CPyInstance();
        startFunctionName = PyUnicode_FromString("_start");
        physicsProcessFunctionName = PyUnicode_FromString("_physics_process");
        endFunctionName = PyUnicode_FromString("_end");
        componentManager = GD::GetContainer()->componentManager;
    }

    void CreateEntityInstance(Entity entity) override {
        ScriptableClassComponent scriptableClassComponent = componentManager->GetComponent<ScriptableClassComponent>(entity);

        // Create Instance
        CPyObject pClassInstance = ExtractClassInstanceFromEntity(entity);
        pClassInstance.AddRef();
        activeClassInstances.emplace(entity, pClassInstance);

        // Call Start
        if (PyObject_HasAttr(pClassInstance, startFunctionName)) {
            // TODO: Invoke in different phase
            PyObject_CallMethod(activeClassInstances[entity], "_start", nullptr);
        }
    }

    void DeleteEntityInstance(Entity entity) override {
        assert(activeClassInstances.count(entity) > 0 && "Entity not registered to python script context!");
        if (PyObject_HasAttr(activeClassInstances[entity], startFunctionName)) {
            // TODO: Invoke in different phase
            PyObject_CallMethod(activeClassInstances[entity], "_end", nullptr);
        }
    }

    void PhysicsProcess(Entity entity, double deltaTime) override {
        assert(activeClassInstances.count(entity) > 0 && "Entity not registered to python script context!");
        if (PyObject_HasAttr(activeClassInstances[entity], physicsProcessFunctionName)) {
            CPyObject processCallValue = PyObject_CallMethod(activeClassInstances[entity], "_physics_process", "(f)", deltaTime);
        }
    }

    void ReceiveSubscribedSignal(Entity subscriberEntity, const std::string &subscriberFunctionName, SignalArguments args) override {}

    void Destroy() override {}
};

#endif //PYTHON_SCRIPT_CONTEXT_H
