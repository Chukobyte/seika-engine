#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <vector>
#include <queue>
#include <unordered_map>
#include <cassert>

#include "entity.h"

class EntityManager {
  private:
    const unsigned int INITIAL_ENTITY_IDS = 1001;
    unsigned int entityIdCounter = INITIAL_ENTITY_IDS + 1;  // Starts at 1 as 0 is invalid
    unsigned int livingEntityCounter = 0;
    std::queue<Entity> availableEntityIds = {};
    std::array<ComponentSignature, MAX_ENTITIES> signatures;
    std::array<ComponentSignature, MAX_ENTITIES> enabledSignatures;

    Entity GetUniqueEntityId() {
        if (availableEntityIds.size() <= 0) {
            availableEntityIds.push(entityIdCounter);
            entityIdCounter++;
        }
        Entity newEntityId = availableEntityIds.front();
        availableEntityIds.pop();
        return newEntityId;
    }
  public:
    EntityManager() {
        for (Entity id = 1; id <= INITIAL_ENTITY_IDS; id++) {
            availableEntityIds.push(id);
        }
    }

    Entity CreateEntity() {
        livingEntityCounter++;
        return GetUniqueEntityId();
    }

    void DestroyEntity(Entity entity) {
        signatures[entity].reset();
        enabledSignatures[entity].reset();

        // TODO: need to fix active id repopulation
        availableEntityIds.push(entity);
        livingEntityCounter--;
    }

    unsigned int GetAliveEntities() {
        return livingEntityCounter;
    }

    void SetSignature(Entity entity, ComponentSignature signature, bool setEnabledSignature = true) {
        signatures[entity] = signature;
        if (setEnabledSignature) {
            enabledSignatures[entity] = signature;
        }
    }

    ComponentSignature GetSignature(Entity entity) const {
        return signatures[entity];
    }

    void SetEnabledSignature(Entity entity, ComponentSignature signature) {
        enabledSignatures[entity] = signature;
    }

    ComponentSignature GetEnabledSignature(Entity entity) const {
        return enabledSignatures[entity];
    }
};

#endif //ENTITY_MANAGER_H
