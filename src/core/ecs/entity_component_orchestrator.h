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

    void AddChildToEntityScene(Entity parentEntity, Entity childEntity) {
        ComponentSignature signature = entityManager->GetSignature(childEntity);
        entitySystemManager->EntitySignatureChanged(childEntity, signature);
        sceneManager->AddChild(parentEntity, childEntity);
    }

    // Will be the function to initialize stuff for a scene
    void RegisterSceneNodeInstances(SceneNode sceneNode) {
        AddChildToEntityScene(sceneNode.parent, sceneNode.entity);
        if (componentManager->HasComponent<ScriptableClassComponent>(sceneNode.entity)) {
            ScriptEntitySystem *scriptEntitySystem = (ScriptEntitySystem*) entitySystemManager->GetEntitySystem<ScriptEntitySystem>();
            scriptEntitySystem->CreateEntityInstance(sceneNode.entity);
        }
        NodeComponent nodeComponent = componentManager->GetComponent<NodeComponent>(sceneNode.entity);
        nodeNameToEntityMap.emplace(nodeComponent.name, sceneNode.entity);

        for (SceneNode childSceneNode : sceneNode.children) {
            RegisterSceneNodeInstances(childSceneNode);
        }
    }

    void CallStartOnScriptInstances(SceneNode sceneNode) {
        for (SceneNode childSceneNode : sceneNode.children) {
            CallStartOnScriptInstances(childSceneNode);
        }
        if (componentManager->HasComponent<ScriptableClassComponent>(sceneNode.entity)) {
            ScriptEntitySystem *scriptEntitySystem = (ScriptEntitySystem*) entitySystemManager->GetEntitySystem<ScriptEntitySystem>();
            scriptEntitySystem->CallStartOnEntityInstance(sceneNode.entity);
        }
    }
  public:
    EntityComponentOrchestrator(EntityManager *entityManagerP, EntitySystemManager *entitySystemManagerP, ComponentManager *componentManagerP, SceneManager *sceneManagerP)
        : entityManager(entityManagerP), entitySystemManager(entitySystemManagerP), componentManager(componentManagerP), sceneManager(sceneManagerP) {
        timerManager = TimerManager::GetInstance();
        signalManager = SignalManager::GetInstance();
    }
    // ENTITY METHODS
    Entity CreateEntity() {
        return entityManager->CreateEntity();
    }

    void NewEntity(SceneNode sceneNode) {
        if (componentManager->HasComponent<ScriptableClassComponent>(sceneNode.entity)) {
            ScriptEntitySystem *scriptEntitySystem = (ScriptEntitySystem*) entitySystemManager->GetEntitySystem<ScriptEntitySystem>();
            scriptEntitySystem->CreateEntityInstance(sceneNode.entity);
        }
    }

    void NewEntityAddChild(Entity parent, Entity child) {
        SceneNode childNode = SceneNode{.entity = child, .parent = parent};
        AddChildToEntityScene(childNode.parent, childNode.entity);
        NodeComponent nodeComponent = componentManager->GetComponent<NodeComponent>(childNode.entity);
        nodeNameToEntityMap.emplace(nodeComponent.name, childNode.entity);
        CallStartOnScriptInstances(childNode);
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
            if (componentManager->HasComponent<NodeComponent>(entityToRemove)) {
                NodeComponent nodeComponent = componentManager->GetComponent<NodeComponent>(entityToRemove);
                nodeNameToEntityMap.erase(nodeComponent.name);
                entityManager->DestroyEntity(entityToRemove);
                componentManager->EntityDestroyed(entityToRemove);
                entitySystemManager->EntityDestroyed(entityToRemove);
                signalManager->RemoveEntitySignals(entityToRemove);
            }
        }
    }

    bool DoesNodeNameExist(const std::string &nodeName) {
        return nodeNameToEntityMap.count(nodeName) > 0;
    }

    Entity GetEntityFromNodeName(const std::string &nodeName) {
        if (DoesNodeNameExist(nodeName)) {
            return nodeNameToEntityMap[nodeName];
        }
        return NO_ENTITY;
    }

    ComponentSignature GetEntitySignature(Entity entity) {
        return entityManager->GetSignature(entity);
    }

    unsigned int GetAliveEntityCount() {
        return entityManager->GetAliveEntities();
    }

    Entity GetEntityParent(Entity entity) {
        return sceneManager->GetParent(entity);
    }

    std::vector<Entity> GetEntityChildren(Entity entity) {
        return sceneManager->GetAllChildEntities(entity);
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
        Logger::GetInstance()->Debug("Changing scene to path '" + scenePathToSwitchTo + "'!");
        Scene scene = sceneManager->LoadSceneFromFile(scenePathToSwitchTo);
        scenePathToSwitchTo.clear();
        RegisterSceneNodeInstances(scene.rootNode);
        CallStartOnScriptInstances(scene.rootNode);
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

    bool IsEntityInCurrentScene(Entity entity) {
        return sceneManager->IsEntityInScene(entity);
    }
};

#endif //ENTITY_COMPONENT_ORCHESTRATOR_H
