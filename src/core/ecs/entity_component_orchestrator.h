#ifndef ENTITY_COMPONENT_ORCHESTRATOR_H
#define ENTITY_COMPONENT_ORCHESTRATOR_H

#include "entity/entity_manager.h"
#include "entity/system/entity_system_manager.h"
#include "component/component_manager.h"

class EntityComponentOrchestrator {
  private:
    EntityManager *entityManager = nullptr;
    EntitySystemManager *entitySystemManager = nullptr;
    ComponentManager *componentManager = nullptr;
  public:
    EntityComponentOrchestrator(EntityManager *entityManagerP, EntitySystemManager *entitySystemManagerP, ComponentManager *componentManagerP)
        : entityManager(entityManagerP), entitySystemManager(entitySystemManagerP), componentManager(componentManagerP) {

    }
    // ENTITY METHODS
    Entity CreateEntity() {
        return entityManager->CreateEntity();
    }

    void DestroyEntity(Entity entity) {
        entityManager->DestroyEntity(entity);

        componentManager->EntityDestroyed(entity);

        entitySystemManager->EntityDestroyed(entity);
    }

    ComponentSignature GetEntitySignature(Entity entity) {
        return entityManager->GetSignature(entity);
    }

    unsigned int GetAliveEntityCount() {
        return entityManager->GetAliveEntities();
    }

    // COMPONENT METHODS
    template<typename T>
    void RegisterComponent() {
        componentManager->RegisterComponent<T>();
    }

    template<typename T>
    void AddComponent(Entity entity, T component) {
        componentManager->AddComponent<T>(entity, component);
        EnableComponent<T>(entity);
    }

    template<typename T>
    void AddComponentWithoutEnabling(Entity entity, T component) {
        componentManager->AddComponent<T>(entity, component);
    }

    template<typename T>
    void UpdateComponent(Entity entity, T component) {
        componentManager->UpdateComponent(entity, component);
    }

    template<typename T>
    void RemoveComponent(Entity entity) {
        componentManager->RemoveComponent<T>(entity);
        DisableComponent<T>(entity);
    }

    template<typename T>
    void EnableComponent(Entity entity) {
        auto signature = entityManager->GetSignature(entity);
        signature.set(componentManager->template GetComponentType<T>(), true);
        entityManager->SetSignature(entity, signature);
        entitySystemManager->EntitySignatureChanged(entity, signature);
    }

    template<typename T>
    void DisableComponent(Entity entity) {
        auto signature = entityManager->GetSignature(entity);
        signature.set(componentManager->template GetComponentType<T>(), false);
        entityManager->SetSignature(entity, signature);
        entitySystemManager->EntitySignatureChanged(entity, signature);
    }

    template<typename T>
    T& GetComponent(Entity entity) {
        return componentManager->GetComponent<T>(entity);
    }

    template<typename T>
    ComponentType GetComponentType() {
        return componentManager->GetComponentType<T>();
    }

    template<typename T>
    bool HasComponent(Entity entity) {
        return componentManager->HasComponent<T>(entity);
    }

    ComponentManager* GetComponentManager() {
        return componentManager;
    }

    // SYSTEM METHODS
    template<typename T>
    T* RegisterSystem() {
        return entitySystemManager->RegisterSystem<T>();
    }

    template<typename T>
    T* GetSystem() {
        return entitySystemManager->GetSystem<T>();
    }

    template<typename T>
    bool HasSystem() {
        return entitySystemManager->HasSystem<T>();
    }

    template<typename T>
    void SetSystemSignature(ComponentSignature signature) {
        entitySystemManager->SetSignature<T>(signature);
    }

    template<typename T>
    ComponentSignature GetSystemSignature() {
        return entitySystemManager->GetSignature<T>();
    }

    void InitializeAllSystems() {
        entitySystemManager->InitializeAllSystems();
    }
};

#endif //ENTITY_COMPONENT_ORCHESTRATOR_H
