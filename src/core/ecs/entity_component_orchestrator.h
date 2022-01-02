#ifndef ENTITY_COMPONENT_ORCHESTRATOR_H
#define ENTITY_COMPONENT_ORCHESTRATOR_H

#include "entity/entity_manager.h"
#include "entity/system/entity_system_manager.h"
#include "component/component_manager.h"
#include "../scene/scene.h"
#include "entity/system/script_entity_system.h"
#include "../signal_manager.h"
#include "../scene/scene_manager.h"

class EntityComponentOrchestrator {
    /*
     * The interface between the engine's systems and ECS (entities and components).
     */
  private:
    EntityManager *entityManager = nullptr;
    EntitySystemManager *entitySystemManager = nullptr;
    ComponentManager *componentManager = nullptr;
    SceneManager *sceneManager = nullptr;
    SignalManager *signalManager = nullptr;
    TimerManager *timerManager = nullptr;

    std::string scenePathToSwitchTo;
    bool removeCurrentSceneAtEndOfUpdate = false;
    std::vector<Entity> entitiesQueuedForDeletion;
    std::map<std::string, Entity> nodeNameToEntityMap;

    void AddChildToEntityScene(Entity parentEntity, Entity childEntity);
    void RegisterSceneNodeInstances(SceneNode sceneNode);
    void CallStartOnScriptInstances(SceneNode sceneNode);

  public:
    EntityComponentOrchestrator(EntityManager *entityManagerP, EntitySystemManager *entitySystemManagerP, ComponentManager *componentManagerP, SceneManager *sceneManagerP);
    // ENTITY METHODS
    Entity CreateEntity();
    void NewEntity(SceneNode sceneNode);
    void NewEntityAddChild(Entity parent, Entity child);
    void QueueEntityForDeletion(Entity entity);
    bool IsEntityQueuedForDeletion(Entity entity);
    void DestroyQueuedEntities();
    void DestroyEntity(SceneNode sceneNode);
    bool DoesNodeNameExist(const std::string &nodeName);
    Entity GetEntityFromNodeName(const std::string &nodeName);
    ComponentSignature GetEntitySignature(Entity entity);
    unsigned int GetAliveEntityCount();
    Entity GetEntityParent(Entity entity);
    std::vector<Entity> GetEntityChildren(Entity entity);

    // COMPONENT METHODS
    template<typename T>
    void RegisterComponent() {
        componentManager->RegisterComponent<T>();
    }

    template<typename T>
    void AddComponent(Entity entity, T component) {
        componentManager->AddComponent<T>(entity, component);
        auto signature = entityManager->GetSignature(entity);
        signature.set(componentManager->GetComponentType<T>(), true);
        entityManager->SetSignature(entity, signature);
    }

    template<typename T>
    void UpdateComponent(Entity entity, T component) {
        componentManager->UpdateComponent(entity, component);
    }

    template<typename T>
    void RemoveComponent(Entity entity) {
        componentManager->RemoveComponent<T>(entity);
        auto signature = entityManager->GetSignature(entity);
        signature.set(componentManager->GetComponentType<T>(), false);
        entityManager->SetSignature(entity, signature);
        entitySystemManager->EntitySignatureChanged(entity, signature);
    }

    template<typename T>
    void EnableComponent(Entity entity) {
        auto signature = entityManager->GetSignature(entity);
        signature.set(componentManager->GetComponentType<T>(), true);
        entitySystemManager->EntitySignatureChanged(entity, signature);
    }

    template<typename T>
    void DisableComponent(Entity entity) {
        auto signature = entityManager->GetSignature(entity);
        signature.set(componentManager->GetComponentType<T>(), false);
        entitySystemManager->EntitySignatureChanged(entity, signature);
    }

    template<typename T>
    bool IsComponentEnabled(Entity entity) {
        auto signature = entityManager->GetSignature(entity);
        return (GetComponentType<T>() & signature) == signature;
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

    void InitializeAllSystems();
    // SCENE METHODS
    void PrepareSceneChange(const std::string &filePath);
    bool HasSceneToSwitchTo() const;
    bool ShouldRemoveCurrentSceneAtEndOfUpdate() const;
    void ChangeSceneTo(const bool loadFromMemory);
    void DestroyCurrentScene();
    bool IsEntityInCurrentScene(Entity entity);
};

#endif //ENTITY_COMPONENT_ORCHESTRATOR_H
