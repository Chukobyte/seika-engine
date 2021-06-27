#ifndef COMPONENT_MANAGER_H
#define COMPONENT_MANAGER_H

#include <unordered_map>
#include <memory>
#include <iostream>

#include "component.h"
#include "component_array.h"

class ComponentManager {
  private:
    std::unordered_map<const char*, ComponentType> componentTypes;
    std::unordered_map<const char*, IComponentArray*> componentArrays;
    unsigned int componentIndex = 0;

    template<typename T>
    ComponentArray<T>* GetComponentArray() {
        const char *typeName = typeid(T).name();

        assert(componentTypes.find(typeName) != componentTypes.end() && "Component not registered before use.");

        return (ComponentArray<T>*) componentArrays[typeName];
    }
  public:
    template<typename T>
    void RegisterComponent() {
        const char *typeName = typeid(T).name();

        assert(componentTypes.find(typeName) == componentTypes.end() && "Registering component type more than once!");

        componentTypes.insert({typeName, componentIndex});

        componentArrays.insert({typeName, new ComponentArray<T>()});

        componentIndex++;
    }

    template<typename T>
    ComponentType GetComponentType() {
        const char *typeName = typeid(T).name();

        assert(componentTypes.find(typeName) != componentTypes.end() && "Component not registered!");

        return componentTypes[typeName];
    }

    template<typename T>
    void AddComponent(Entity entity, T component) {
        GetComponentArray<T>()->InsertNewData(entity, component);
    }

    template<typename T>
    void UpdateComponent(Entity entity, T component) {
        GetComponentArray<T>()->UpdateData(entity, component);
    }

    template<typename T>
    void RemoveComponent(Entity entity) {
        GetComponentArray<T>()->RemoveData(entity);
    }

    template<typename T>
    T& GetComponent(Entity entity) {
        return GetComponentArray<T>()->GetData(entity);
    }

    template<typename T>
    bool HasComponent(Entity entity) {
        return GetComponentArray<T>()->HasData(entity);
    }

    void EntityDestroyed(Entity entity) {
        for (auto const &pair : componentArrays) {
            auto const &component = pair.second;
            component->EntityDestroyed(entity);
        }
    }
};

#endif //COMPONENT_MANAGER_H
