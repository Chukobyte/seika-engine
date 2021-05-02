#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <vector>
#include <queue>
#include <unordered_map>
#include <cassert>

#include "entity.h"

class EntityManager {
  private:
    unsigned int entityIdCounter = 1;  // Starts at 1 as 0 is invalid
    unsigned int livingEntityCounter = 0;
    std::queue<Entity> availableEntityIds;
    std::array<ComponentSignature, MAX_ENTITIES> signatures;
    std::vector<Entity> entitiesToDelete;

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

    Entity CreateEntity() {
        assert(livingEntityCounter < MAX_ENTITIES && "Too many entities to create!");

        livingEntityCounter++;

        return GetUniqueEntityId();
    }

    void DestroyEntity(Entity entity) {
        assert(entity < MAX_ENTITIES && "Entity out of range!");

        signatures[entity].reset();

        availableEntityIds.push(entity);
        entitiesToDelete.insert(entitiesToDelete.end(), 1, entity);
        livingEntityCounter--;
    }

    void DeleteEntitiesQueuedForDeletion() {
        for (Entity entity : entitiesToDelete) {
            availableEntityIds.push(entity);
        }
        entitiesToDelete.clear();
    }

    void SetSignature(Entity entity, ComponentSignature signature) {
        assert(entity < MAX_ENTITIES && "Entity out of range!");

        signatures[entity] = signature;
    }

    ComponentSignature GetSignature(Entity entity) {
        assert(entity < MAX_ENTITIES && "Entity out of range!");

        return signatures[entity];
    }
};

#endif //ENTITY_MANAGER_H
