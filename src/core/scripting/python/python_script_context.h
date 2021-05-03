#ifndef PYTHON_SCRIPT_CONTEXT_H
#define PYTHON_SCRIPT_CONTEXT_H

#include <map>

#include "../script_context.h"
#include "pyhelper.hpp"

class PythonScriptContext : public ScriptContext {
  public:
    CPyInstance *pyInstance = nullptr;
    std::map<Entity, CPyObject> activeClassInstances;
    std::map<Entity, int> instanceScriptFunctionFlags;
    CPyObject startFunctionName;
    CPyObject processFunctionName;
    CPyObject endFunctionName;

    ~PythonScriptContext() {
        delete pyInstance;
    }

    void Initialize() override {
        pyInstance = new CPyInstance();
        startFunctionName = PyUnicode_FromString("_start");
        processFunctionName = PyUnicode_FromString("_process");
        endFunctionName = PyUnicode_FromString("_end");
    }

    void CreateEntityInstance(Entity entity) override {}

    void DeleteEntityInstance(Entity entity) override {}

    void PhysicsProcess(Entity entity, float deltaTime) override {}

    void ReceiveSubscribedSignal(Entity subscriberEntity, const std::string &subscriberFunctionName, SignalArguments args) override {}

    void Destroy() override {}
};

#endif //PYTHON_SCRIPT_CONTEXT_H
