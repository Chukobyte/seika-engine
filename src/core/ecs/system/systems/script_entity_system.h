#ifndef SCRIPT_ENTITY_SYSTEM_H
#define SCRIPT_ENTITY_SYSTEM_H

#include "../entity_system.h"
#include "../../../scripting/script_context.h"
#include "../../component/components/transform2D_component.h"
#include "../../component/components/text_label_component.h"

class ScriptEntitySystem : public EntitySystem {
  private:
    ScriptContext *activeScriptContext = nullptr;
  public:
    std::unordered_map<const char*, ScriptContext*> scriptContexts;

    ScriptEntitySystem() {
        enabled = true;
    }

    void Initialize() override {
        for (auto const &pair : scriptContexts) {
            auto const &scriptContext = pair.second;
            scriptContext->Initialize();
        }
    }

    void Enable() override {}

    void Disable() override {}

    void OnEntityDestroyed(Entity entity) override {
        assert(activeScriptContext != nullptr && "No active script context!");
        activeScriptContext->DeleteEntityInstance(entity);
    }

    template<typename T>
    T* InstallScriptContext() {
        const char *typeName = typeid(T).name();
        assert(!HasScriptContext<T>() && "Installing script context more than once");
        auto *scriptContext = new T();
        scriptContexts.emplace(typeName, scriptContext);
        if (activeScriptContext == nullptr) {
            SetActiveScriptContext<T>();
        }
        return scriptContext;
    }

    template<typename T>
    void SetActiveScriptContext() {
        assert(HasScriptContext<T>() && "Script context is not installed!");
        const char *typeName = typeid(T).name();
        activeScriptContext = scriptContexts[typeName];
    }

    template<typename T>
    bool HasScriptContext() {
        const char *typeName = typeid(T).name();
        return scriptContexts.find(typeName) != scriptContexts.end();
    }

    void CreateEntityInstance(const Entity entity) {
        assert(activeScriptContext != nullptr && "No active script context!");
        activeScriptContext->CreateEntityInstance(entity);
    }

    void CallStartOnEntityInstance(const Entity entity) {
        assert(activeScriptContext != nullptr && "No active script context!");
        activeScriptContext->CallStartOnEntityInstance(entity);
    }

    void PhysicsProcess(float deltaTime) override {
        assert(activeScriptContext != nullptr && "No active script context!");
        for (Entity entity : entities) {
            activeScriptContext->PhysicsProcess(entity, deltaTime);
        }
        activeScriptContext->FlushStdOutBuffer();
    }

    void ReceiveSubscribedSignal(const Entity subscriberEntity, const std::string &subscriberFunctionName, const SignalArguments args) {
        assert(activeScriptContext != nullptr && "No active script context!");
        activeScriptContext->ReceiveSubscribedSignal(subscriberEntity, subscriberFunctionName, args);
    }

};

#endif //SCRIPT_ENTITY_SYSTEM_H
