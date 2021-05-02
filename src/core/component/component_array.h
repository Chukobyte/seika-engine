#ifndef COMPONENT_ARRAY_H
#define COMPONENT_ARRAY_H

#include <unordered_map>
#include <cassert>

#include "../entity.h"
#include "component.h"

class IComponentArray {
  public:
    virtual ~IComponentArray() = default;
    virtual void EntityDestroyed(Entity entity) = 0;
};

template<typename T>
class ComponentArray : public IComponentArray {
  private:
    std::array<T, MAX_ENTITIES> components;
    std::unordered_map<Entity, size_t> entityToIndexMap;
    std::unordered_map<size_t, Entity> indexToEntityMap;
    size_t size = 0;
  public:
    void InsertNewData(Entity entity, T component) {
        assert(entityToIndexMap.find(entity) == entityToIndexMap.end() && "Component added to same entity more than once!");

        size_t newIndex = size;
        entityToIndexMap[entity] = newIndex;
        indexToEntityMap[newIndex] = entity;
        components[newIndex] = component;

        size++;
    }

    void UpdateData(Entity entity, T component) {
        assert(entityToIndexMap.find(entity) != entityToIndexMap.end() && "Component hasn't been added!");

        components[entityToIndexMap[entity]] = component;
    }

    void RemoveData(Entity entity) {
        assert(entityToIndexMap.find(entity) != entityToIndexMap.end() && "Removing non-existent component!");

        // Copy element at end into deleted element's place to maintain array density
        size_t indexOfRemovedEntity = entityToIndexMap[entity];
        size_t indexOfLastElement = size - 1;
        components[indexOfRemovedEntity] = components[indexOfLastElement];

        // Update map to point to moved spot
        Entity entityOfLastElement = indexToEntityMap[indexOfLastElement];
        entityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
        indexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

        entityToIndexMap.erase(entity);
        indexToEntityMap.erase(indexOfLastElement);

        size--;
    }

    T& GetData(Entity entity) {
        assert(entityToIndexMap.find(entity) != entityToIndexMap.end() && "Retrieving non-existent component!");

        return components[entityToIndexMap[entity]];
    }

    bool HasData(Entity entity) {
        return entityToIndexMap.find(entity) != entityToIndexMap.end();
    }

    void EntityDestroyed(Entity entity) override {
        if (entityToIndexMap.find(entity) != entityToIndexMap.end()) {
            RemoveData(entity);
        }
    }
};

#endif //COMPONENT_ARRAY_H
