#include "entity_component_orchestrator.h"
#include "component/components/scriptable_class_component.h"

EntityComponentOrchestrator::EntityComponentOrchestrator(EntityManager *entityManagerP, EntitySystemManager *entitySystemManagerP, ComponentManager *componentManagerP, SceneManager *sceneManagerP)
    : entityManager(entityManagerP), entitySystemManager(entitySystemManagerP), componentManager(componentManagerP), sceneManager(sceneManagerP) {
    timerManager = TimerManager::GetInstance();
    signalManager = SignalManager::GetInstance();
}
// ENTITY METHODS
Entity EntityComponentOrchestrator::CreateEntity() {
    return entityManager->CreateEntity();
}

// TODO: Make into hook
void EntityComponentOrchestrator::NewEntity(SceneNode sceneNode) {
    if (componentManager->HasComponent<ScriptableClassComponent>(sceneNode.entity)) {
        ScriptEntitySystem *scriptEntitySystem = (ScriptEntitySystem*) entitySystemManager->GetEntitySystem<ScriptEntitySystem>();
        scriptEntitySystem->CreateEntityInstance(sceneNode.entity);
    }
}

void EntityComponentOrchestrator::QueueEntityForDeletion(Entity entity) {
    entitiesQueuedForDeletion.emplace_back(entity);
}

bool EntityComponentOrchestrator::IsEntityQueuedForDeletion(Entity entity) {
    return std::find(entitiesQueuedForDeletion.begin(), entitiesQueuedForDeletion.end(), entity) != entitiesQueuedForDeletion.end();
}

void EntityComponentOrchestrator::DestroyQueuedEntities() {
    for (Entity entity : entitiesQueuedForDeletion) {
        if (sceneManager->HasEntitySceneNode(entity)) {
            SceneNode sceneNode = sceneManager->GetEntitySceneNode(entity);
            DestroyEntity(sceneNode);
        }
    }
    entitiesQueuedForDeletion.clear();
}

void EntityComponentOrchestrator::DestroyEntity(SceneNode sceneNode) {
    sceneManager->RemoveNode(sceneNode);
    std::vector<Entity> entitiesRemovedFromScene = sceneManager->FlushRemovedEntities();
    for (Entity entityToRemove : entitiesRemovedFromScene) {
        if (componentManager->HasComponent<NodeComponent>(entityToRemove)) {
            NodeComponent nodeComponent = componentManager->GetComponent<NodeComponent>(entityToRemove);
            nodeNameToEntityMap.erase(nodeComponent.name);
            entityManager->DestroyEntity(entityToRemove);
            componentManager->EntityDestroyed(entityToRemove);
            entitySystemManager->EntityDestroyed(entityToRemove, nodeComponent.tags);
            signalManager->RemoveEntitySignals(entityToRemove);
        }
    }
}

bool EntityComponentOrchestrator::DoesNodeNameExist(const std::string &nodeName) {
    return nodeNameToEntityMap.count(nodeName) > 0;
}

Entity EntityComponentOrchestrator::GetEntityFromNodeName(const std::string &nodeName) {
    if (DoesNodeNameExist(nodeName)) {
        return nodeNameToEntityMap[nodeName];
    }
    return NULL_ENTITY;
}

ComponentSignature EntityComponentOrchestrator::GetEntitySignature(Entity entity) {
    return entityManager->GetSignature(entity);
}

unsigned int EntityComponentOrchestrator::GetAliveEntityCount() {
    return entityManager->GetAliveEntities();
}

Entity EntityComponentOrchestrator::GetEntityParent(Entity entity) {
    return sceneManager->GetParent(entity);
}

std::vector<Entity> EntityComponentOrchestrator::GetEntityChildren(Entity entity) {
    return sceneManager->GetAllChildEntities(entity);
}

// SYSTEM
void EntityComponentOrchestrator::InitializeAllSystems() {
    entitySystemManager->InitializeAllSystems();
}

// SCENE
void EntityComponentOrchestrator::AddChildToEntityScene(Entity parentEntity, Entity childEntity) {
    ComponentSignature signature = entityManager->GetEnabledSignature(childEntity);
    entitySystemManager->EntitySignatureChanged(childEntity, signature);
    sceneManager->AddChild(parentEntity, childEntity);
}

// Used when adding a new entity to a scene from scripting
void EntityComponentOrchestrator::NewEntityAddChild(Entity parent, Entity child) {
    SceneNode childNode = SceneNode{.entity = child, .parent = parent};
    AddChildToEntityScene(childNode.parent, childNode.entity);
    NodeComponent nodeComponent = componentManager->GetComponent<NodeComponent>(childNode.entity);
    nodeNameToEntityMap.emplace(nodeComponent.name, childNode.entity);
    entitySystemManager->OnEntityTagsUpdatedSystemsHook(child, {}, nodeComponent.tags);
    CallStartOnScriptInstances(childNode);
}

// Will be the function to initialize stuff for a scene
void EntityComponentOrchestrator::RegisterSceneNodeInstances(SceneNode sceneNode) {
    AddChildToEntityScene(sceneNode.parent, sceneNode.entity);
    if (componentManager->HasComponent<ScriptableClassComponent>(sceneNode.entity)) {
        ScriptEntitySystem *scriptEntitySystem = (ScriptEntitySystem*) entitySystemManager->GetEntitySystem<ScriptEntitySystem>();
        scriptEntitySystem->CreateEntityInstance(sceneNode.entity);
    }
    NodeComponent nodeComponent = componentManager->GetComponent<NodeComponent>(sceneNode.entity);
    nodeNameToEntityMap.emplace(nodeComponent.name, sceneNode.entity);
    entitySystemManager->OnEntityTagsUpdatedSystemsHook(sceneNode.entity, {}, nodeComponent.tags);

    for (SceneNode childSceneNode : sceneNode.children) {
        RegisterSceneNodeInstances(childSceneNode);
    }
}

void EntityComponentOrchestrator::CallStartOnScriptInstances(SceneNode sceneNode) {
    for (SceneNode childSceneNode : sceneNode.children) {
        CallStartOnScriptInstances(childSceneNode);
    }
    if (componentManager->HasComponent<ScriptableClassComponent>(sceneNode.entity)) {
        ScriptEntitySystem *scriptEntitySystem = (ScriptEntitySystem*) entitySystemManager->GetEntitySystem<ScriptEntitySystem>();
        scriptEntitySystem->CallStartOnEntityInstance(sceneNode.entity);
    }
}

void EntityComponentOrchestrator::PrepareSceneChange(const std::string &filePath) {
    scenePathToSwitchTo = filePath;
    removeCurrentSceneAtEndOfUpdate = true;
}

bool EntityComponentOrchestrator::HasSceneToSwitchTo() const {
    return !scenePathToSwitchTo.empty();
}

bool EntityComponentOrchestrator::ShouldRemoveCurrentSceneAtEndOfUpdate() const {
    return removeCurrentSceneAtEndOfUpdate;
}

void EntityComponentOrchestrator::ChangeSceneTo(const bool loadFromMemory) {
    Logger::GetInstance()->Debug("Changing scene to path '" + scenePathToSwitchTo + "'!");
    Scene scene;
    if (loadFromMemory) {
        scene = sceneManager->LoadSceneFromMemory(scenePathToSwitchTo);
    } else {
        scene = sceneManager->LoadSceneFromFile(scenePathToSwitchTo);
    }
    scenePathToSwitchTo.clear();
    RegisterSceneNodeInstances(scene.rootNode);
    CallStartOnScriptInstances(scene.rootNode);
}

void EntityComponentOrchestrator::DestroyCurrentScene() {
    Scene currentScene = sceneManager->GetCurrentScene();
    if (currentScene.rootNode.entity != NULL_ENTITY) {
        DestroyEntity(currentScene.rootNode);
    }
    removeCurrentSceneAtEndOfUpdate = false;
}

bool EntityComponentOrchestrator::IsEntityInCurrentScene(Entity entity) {
    return sceneManager->IsEntityInScene(entity);
}
