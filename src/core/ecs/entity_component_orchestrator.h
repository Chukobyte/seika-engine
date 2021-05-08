#ifndef ENTITY_COMPONENT_ORCHESTRATOR_H
#define ENTITY_COMPONENT_ORCHESTRATOR_H

#include "entity/entity_manager.h"
#include "entity/system/entity_system_manager.h"
#include "component/component_manager.h"
#include "../scene/scene.h"
#include "entity/system/script_entity_system.h"

class EntityComponentOrchestrator {
    /*
     * The interface between the engine's systems and ECS (entities and components).
     */
  private:
    EntityManager *entityManager = nullptr;
    EntitySystemManager *entitySystemManager = nullptr;
    ComponentManager *componentManager = nullptr;
    SceneManager *sceneManager = nullptr;

    std::string scenePathToSwitchTo;
    bool removeCurrentSceneAtEndOfUpdate = false;
    std::vector<Entity> entitiesQueuedForDeletion;

    // Will be the function to initialize stuff for a scene
    void RegisterAllNodeSystemSignatures(SceneNode sceneNode) {
        for (SceneNode childSceneNode : sceneNode.children) {
            RegisterAllNodeSystemSignatures(childSceneNode);
        }
        AddChildToEntityScene(sceneNode.parent, sceneNode.entity);
        if (componentManager->HasComponent<ScriptableClassComponent>(sceneNode.entity)) {
            ScriptEntitySystem *scriptEntitySystem = (ScriptEntitySystem*) entitySystemManager->GetEntitySystem<ScriptEntitySystem>();
            scriptEntitySystem->CreateEntityInstance(sceneNode.entity);
        }
    }
  public:
    EntityComponentOrchestrator(EntityManager *entityManagerP, EntitySystemManager *entitySystemManagerP, ComponentManager *componentManagerP, SceneManager *sceneManagerP)
        : entityManager(entityManagerP), entitySystemManager(entitySystemManagerP), componentManager(componentManagerP), sceneManager(sceneManagerP) {

    }
    // ENTITY METHODS
    Entity CreateEntity() {
        return entityManager->CreateEntity();
    }

    void QueueEntityForDeletion(Entity entity) {
        entitiesQueuedForDeletion.emplace_back(entity);
    }

    bool IsEntityQueuedForDeletion(Entity entity) {
        return std::find(entitiesQueuedForDeletion.begin(), entitiesQueuedForDeletion.end(), entity) != entitiesQueuedForDeletion.end();
    }

    void DestroyQueuedEntities() {
        for (Entity entity : entitiesQueuedForDeletion) {
            if (sceneManager->HasEntitySceneNode(entity)) {
                SceneNode sceneNode = sceneManager->GetEntitySceneNode(entity);
                DestroyEntity(sceneNode);
            }
        }
        entitiesQueuedForDeletion.clear();
    }

    void DestroyEntity(SceneNode sceneNode) {
        sceneManager->RemoveNode(sceneNode);
        std::vector<Entity> entitiesRemovedFromScene = sceneManager->FlushRemovedEntities();
        for (Entity entityToRemove : entitiesRemovedFromScene) {
            entityManager->DestroyEntity(entityToRemove);
            componentManager->EntityDestroyed(entityToRemove);
            entitySystemManager->EntityDestroyed(entityToRemove);
        }
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
    // SCENE METHODS
    void PrepareSceneChange(const std::string &filePath) {
        scenePathToSwitchTo = filePath;
        removeCurrentSceneAtEndOfUpdate = true;
    }

    bool HasSceneToSwitchTo() {
        return !scenePathToSwitchTo.empty();
    }

    bool ShouldRemoveCurrentSceneAtEndOfUpdate() {
        return removeCurrentSceneAtEndOfUpdate;
    }

    void ChangeSceneTo() {
        Scene scene = sceneManager->LoadSceneFromFile(scenePathToSwitchTo);
        scenePathToSwitchTo.clear();
        RegisterAllNodeSystemSignatures(scene.rootNode);
    }

    void DestroyCurrentScene() {
        Scene currentScene = sceneManager->GetCurrentScene();
        if (currentScene.rootNode.entity != NO_ENTITY) {
            DestroyEntity(currentScene.rootNode);
        }
        removeCurrentSceneAtEndOfUpdate = false;
    }

//    void PrepareSceneChange(Entity rootNodeEntity) {
//        sceneManager->ChangeToScene(rootNodeEntity);
//    }

    void AddChildToEntityScene(Entity parentEntity, Entity childEntity) {
        ComponentSignature signature = entityManager->GetSignature(childEntity);
        entitySystemManager->EntitySignatureChanged(childEntity, signature);
        sceneManager->AddChild(parentEntity, childEntity);
    }

    bool IsEntityInCurrentScene(Entity entity) {
        return sceneManager->IsEntityInScene(entity);
    }

    Entity GetSceneNodeParent(Entity entity) {
        return sceneManager->GetParent(entity);
    }
};

#endif //ENTITY_COMPONENT_ORCHESTRATOR_H
