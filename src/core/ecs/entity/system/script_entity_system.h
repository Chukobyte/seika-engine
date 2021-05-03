#ifndef SCRIPT_ENTITY_SYSTEM_H
#define SCRIPT_ENTITY_SYSTEM_H

#include "entity_system.h"
#include "../../../scripting/script_context.h"
#include "../../component/components/transform2D_component.h"
#include "../../component/components/text_label_component.h"

class ScriptEntitySystem : public EntitySystem {
  public:
    std::unordered_map<const char*, ScriptContext*> scriptContexts;

    ScriptEntitySystem() {
        enabled = true;
    }

    void Enable() override {}
    void Disable() override {}

    template<typename T>
    T* InstallScriptContext() {
        const char *typeName = typeid(T).name();
        assert(HasScriptContext<T>() && "Installing script context more than once");
        auto scriptContext = new T();
        scriptContexts.emplace(typeName, scriptContext);

    }

    template<typename T>
    bool HasScriptContext() {
        const char *typeName = typeid(T).name();
        return scriptContexts.find(typeName) == scriptContexts.end();
    }

    void Initialize() {
        for (auto const &pair : scriptContexts) {
            auto const &type = pair.first;
            auto const &scriptContext = pair.second;
            scriptContext->Initialize();
        }
    }

    void CreateEntityInstance(Entity entity) {
        for (auto const &pair : scriptContexts) {
            auto const &type = pair.first;
            auto const &scriptContext = pair.second;
            scriptContext->CreateEntityInstance(entity);
        }
    }

    void DeleteEntityInstance(Entity entity) {
        for (auto const &pair : scriptContexts) {
            auto const &type = pair.first;
            auto const &scriptContext = pair.second;
            scriptContext->DeleteEntityInstance(entity);
        }
    }

    void PhysicsProcess(double deltaTime) {
        for (auto const &pair : scriptContexts) {
            auto const &type = pair.first;
            auto const &scriptContext = pair.second;
            for (Entity entity : entities) {
                scriptContext->PhysicsProcess(entity, deltaTime);
            }
        }
    }

    void ReceiveSubscribedSignal(Entity subscriberEntity, const std::string &subscriberFunctionName, SignalArguments args) {
        for (auto const &pair : scriptContexts) {
            auto const &type = pair.first;
            auto const &scriptContext = pair.second;
            scriptContext->ReceiveSubscribedSignal(subscriberEntity, subscriberFunctionName, args);
        }
    }

};

#endif //SCRIPT_ENTITY_SYSTEM_H
