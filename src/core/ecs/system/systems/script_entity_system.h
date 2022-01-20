#pragma once

#include "../entity_system.h"

#include <algorithm>

#include "../../../scripting/script_context.h"
#include "../../component/components/transform2D_component.h"
#include "../../component/components/text_label_component.h"

class ScriptEntitySystem : public EntitySystem {
  private:
    ScriptContext *activeScriptContext = nullptr;
    std::vector<Entity> processEntities = {};
    std::vector<Entity> physicsProcessEntities = {};
  public:
    std::unordered_map<const char*, ScriptContext*> scriptContexts;

    ScriptEntitySystem() {
        enabled = true;
    }

    void Initialize() override {
        EntitySystem::Initialize();
        for (auto const &pair : scriptContexts) {
            auto const &scriptContext = pair.second;
            scriptContext->Initialize();
        }
    }

    void OnEntityDestroyed(Entity entity) override {
        EntitySystem::OnEntityDestroyed(entity);
        assert(activeScriptContext != nullptr && "No active script context!");
        activeScriptContext->DeleteEntityInstance(entity);
        processEntities.erase(std::remove(processEntities.begin(), processEntities.end(), entity), processEntities.end());
        physicsProcessEntities.erase(std::remove(physicsProcessEntities.begin(), physicsProcessEntities.end(), entity), physicsProcessEntities.end());
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
        if (activeScriptContext->EntityHasProcessFunction(entity)) {
            processEntities.emplace_back(entity);
        }
        if (activeScriptContext->EntityHasPhysicsProcessFunction(entity)) {
            physicsProcessEntities.emplace_back(entity);
        }
    }

    void Process(float deltaTime) override {
        assert(activeScriptContext != nullptr && "No active script context!");
        for (Entity entity : processEntities) {
            activeScriptContext->Process(entity, deltaTime);
        }
    }

    void PhysicsProcess(float deltaTime) override {
        assert(activeScriptContext != nullptr && "No active script context!");
        for (Entity entity : physicsProcessEntities) {
            activeScriptContext->PhysicsProcess(entity, deltaTime);
        }
        activeScriptContext->FlushStdOutBuffer();
    }

    void ReceiveSubscribedSignal(const Entity subscriberEntity, const std::string &subscriberFunctionName, const SignalArguments args) {
        assert(activeScriptContext != nullptr && "No active script context!");
        activeScriptContext->ReceiveSubscribedSignal(subscriberEntity, subscriberFunctionName, args);
    }
};
