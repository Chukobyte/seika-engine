#pragma once

#include "../../utils/singleton.h"

#include <cassert>
#include <unordered_map>

#include "../entity/entity.h"
#include "entity_system.h"
#include "../../utils/logger.h"
#include "../../utils/helper.h"

enum class EntitySystemHook : int {
    NONE = 0,
    PROCESS = 2,
    PHYSICS_PROCESS = 4,
    RENDER = 8,
    ON_ENTITY_TAGS_UPDATE = 16,
    ALL = PROCESS | PHYSICS_PROCESS | RENDER | ON_ENTITY_TAGS_UPDATE,
};
GENERATE_ENUM_CLASS_OPERATORS(EntitySystemHook)

class EntitySystemManager : public Singleton<EntitySystemManager> {
  private:
    Logger *logger = nullptr;
    std::unordered_map<const char*, ComponentSignature> signatures{};
    std::unordered_map<const char*, EntitySystem*> systems{};
    // Subscribable systems
    std::vector<EntitySystem*> processSystems = {};
    std::vector<EntitySystem*> physicsProcessSystems = {};
    std::vector<EntitySystem*> renderSystems = {};
    std::vector<EntitySystem*> onEntityTagsUpdatedSystems = {};

    void ProcessSystemHooks(EntitySystem* system, EntitySystemHook systemHooks) {
        if (systemHooks == EntitySystemHook::NONE) {
            return;
        }
        if ((systemHooks & EntitySystemHook::PROCESS) == EntitySystemHook::PROCESS) {
            processSystems.emplace_back(system);
        }
        if ((systemHooks & EntitySystemHook::PHYSICS_PROCESS) == EntitySystemHook::PHYSICS_PROCESS) {
            physicsProcessSystems.emplace_back(system);
        }
        if ((systemHooks & EntitySystemHook::RENDER) == EntitySystemHook::RENDER) {
            renderSystems.emplace_back(system);
        }
        if ((systemHooks & EntitySystemHook::ON_ENTITY_TAGS_UPDATE) == EntitySystemHook::ON_ENTITY_TAGS_UPDATE) {
            onEntityTagsUpdatedSystems.emplace_back(system);
        }
    }

  public:
    EntitySystemManager(singleton) : logger(Logger::GetInstance()) {}

    template<typename T>
    T* GetSystem() {
        const char *typeName = typeid(T).name();
        assert(HasSystem<T>() && "System used before registered.");
        return (T*) systems[typeName];
    }

    template<typename T>
    T* RegisterSystem(EntitySystemHook systemHooks = EntitySystemHook::NONE) {
        const char *typeName = typeid(T).name();

        assert(!HasSystem<T>() && "Registering system more than once.");

        auto *system = new T();
        system->Enable();
        systems.insert({typeName, system});
        ProcessSystemHooks(system, systemHooks);
        return system;
    }

    template<typename T>
    bool HasSystem() {
        const char *typeName = typeid(T).name();
        return systems.find(typeName) != systems.end();
    }

    template<typename T>
    EntitySystem* GetEntitySystem() {
        const char *typeName = typeid(T).name();
        assert(HasSystem<T>() && "System used before registered.");
        return systems[typeName];
    }

    template<typename T>
    void EnableSystem() {
        EntitySystem* system = GetSystem<T>();
        if (!system->IsEnabled()) {
            system->Enable();
        } else {
            logger->Warn("System already enabled!");
        }
    }

    template<typename T>
    void DisableSystem() {
        EntitySystem* system = GetSystem<T>();
        if (system->IsEnabled()) {
            system->Disable();
        } else {
            logger->Warn("System already disabled!");
        }
    }

    template<typename T>
    void SetSignature(ComponentSignature signature) {
        const char* typeName = typeid(T).name();

        assert(HasSystem<T>() && "System used before registered.");

        signatures.insert({typeName, signature});
    }

    template<typename T>
    ComponentSignature GetSignature() {
        const char* typeName = typeid(T).name();

        assert(HasSystem<T>() && "System hasn't been registered!");

        return signatures[typeName];
    }

    void InitializeAllSystems() {
        for (auto const& pair : systems) {
            auto const& system = pair.second;
            system->Initialize();
        }
    }

    void EntityDestroyed(Entity entity, const std::vector<std::string>& tags) {
        for (auto const& pair : systems) {
            auto const& system = pair.second;
            system->OnEntityDestroyed(entity);
        }
        for (EntitySystem *tagSystem : onEntityTagsUpdatedSystems) {
            tagSystem->OnEntityTagsRemoved(entity, tags);
        }
    }

    void EntitySignatureChanged(Entity entity, ComponentSignature entitySignature) {
        // Notify each system that an entity's signature changed
        for (auto const& pair : systems) {
            auto const& type = pair.first;
            auto const& system = pair.second;
            auto const& systemSignature = signatures[type];

            // Entity signature matches system signature - insert into set
            if ((entitySignature & systemSignature) == systemSignature) {
                system->OnRegisterEntity(entity);
            }
            // Entity signature does not match system signature - erase from set
            else {
                system->OnUnRegisterEntity(entity);
            }
        }
    }

    void ProcessSystemsHook(float deltaTime) {
        for (EntitySystem* system : processSystems) {
            system->Process(deltaTime);
        }
    }

    void PhysicsProcessSystemsHook(float deltaTime) {
        for (EntitySystem* system : physicsProcessSystems) {
            system->PhysicsProcess(deltaTime);
        }
    }

    void RenderSystemsHook() {
        for (EntitySystem* system : renderSystems) {
            system->Render();
        }
    }

    void OnEntityTagsUpdatedSystemsHook(Entity entity, const std::vector<std::string>& oldTags, const std::vector<std::string>& newTags) {
        for (EntitySystem *tagSystem : onEntityTagsUpdatedSystems) {
            if (tagSystem->HasEntity(entity)) {
                tagSystem->OnEntityTagsUpdated(entity, oldTags, newTags);
            }
        }
    }
};
