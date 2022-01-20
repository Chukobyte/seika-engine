#include "scene_manager.h"
#include "../ecs/component/components/transform3D_component.h"

SceneManager::SceneManager(SceneContext *vSceneContext, EntityManager *vEntityManager, ComponentManager *vComponentManager, AssetManager *vAssetManager) :
    sceneContext(vSceneContext), entityManager(vEntityManager), componentManager(vComponentManager), assetManager(vAssetManager) {
    timerManager = TimerManager::GetInstance();
    archiveLoader = ArchiveLoader::GetInstance();
    sceneNodeLoader = SceneNodeLoader(entityManager, componentManager, assetManager, timerManager);
}

Scene SceneManager::GetCurrentScene() {
    return currentScene;
}

SceneNode SceneManager::GetEntitySceneNode(Entity entity) {
    if (!HasEntitySceneNode(entity)) {
        Logger::GetInstance()->Error("Doesn't have entity " + std::to_string(entity));
    }
    assert(HasEntitySceneNode(entity) && "Tried to get scene node that doesn't exist!");
    return entityToSceneNodeMap[entity];
}

bool SceneManager::HasEntitySceneNode(Entity entity) const {
    return entityToSceneNodeMap.count(entity) > 0;
}

void SceneManager::ChangeToScene(Scene scene) {
    currentScene = scene;
    sceneContext->currentSceneEntity = currentScene.rootNode.entity;
    entityToMainScenesMap.emplace(currentScene.rootNode.entity, currentScene);
    AddChild(NULL_ENTITY, currentScene.rootNode.entity);
}

void SceneManager::AddChild(Entity parent, Entity child) {
    SceneNode childNode = SceneNode{.entity = child, .parent = parent};
    if (parent != NULL_ENTITY) {
        assert((entityToSceneNodeMap.count(parent) > 0) && "Parent scene node doesn't exist!");
        entityToSceneNodeMap.emplace(childNode.entity, childNode);
        Entity currentParent = parent;
        Entity currentChild = child;
        while (currentParent != NULL_ENTITY) {
            entityToSceneNodeMap[currentParent].children.emplace_back(entityToSceneNodeMap[currentChild]);
            if (currentParent == currentScene.rootNode.entity) {
                currentScene.rootNode.children.emplace_back(childNode);
            }
            currentChild = entityToSceneNodeMap[currentParent].entity;
            currentParent = entityToSceneNodeMap[currentParent].parent;
        }
    } else {
        entityToSceneNodeMap.emplace(childNode.entity, childNode);
    }
}

std::vector<Entity> SceneManager::GetAllChildEntities(Entity entity) {
    std::vector<Entity> childrenEntities;
    SceneNode parentNode = GetEntitySceneNode(entity);
    for (SceneNode childNode : parentNode.children) {
        if (IsEntityInScene(childNode.entity)) {
            childrenEntities.emplace_back(childNode.entity);
        }
    }
    return childrenEntities;
}

Entity SceneManager::GetParent(Entity entity) {
    if (IsEntityInScene(entity)) {
        SceneNode sceneNode = entityToSceneNodeMap[entity];
        return sceneNode.parent;
    }
    return NULL_ENTITY;
}

void SceneManager::RemoveNode(SceneNode sceneNode) {
    for (SceneNode childNode : sceneNode.children) {
        RemoveNode(childNode);
    }
    entityToSceneNodeMap.erase(sceneNode.entity);
    entityToMainScenesMap.erase(sceneNode.entity);
    entitiesRecentlyRemoved.emplace_back(sceneNode.entity);
}

std::vector<Entity> SceneManager::FlushRemovedEntities() {
    std::vector<Entity> removedEntitiesCopy = entitiesRecentlyRemoved;
    entitiesRecentlyRemoved.clear();
    return removedEntitiesCopy;
}

bool SceneManager::IsEntityInScene(Entity entity) const {
    return entityToSceneNodeMap.count(entity) > 0;
}

Scene SceneManager::LoadSceneFromFile(const std::string &filePath) {
    nlohmann::json sceneJson = JsonFileHelper::LoadJsonFile(filePath);
    SceneNode rootNode = sceneNodeLoader.ParseSceneJson(sceneJson, true);
    Scene loadedScene = Scene{.rootNode = rootNode};
    ChangeToScene(loadedScene);
    return loadedScene;
}

Scene SceneManager::LoadSceneFromMemory(const std::string &filePath) {
    const std::string &sceneArchiveJsonString = archiveLoader->LoadAsString(filePath);
    nlohmann::json sceneJson = JsonFileHelper::ConvertStringToJson(sceneArchiveJsonString);
    SceneNode rootNode = sceneNodeLoader.ParseSceneJson(sceneJson, true);
    Scene loadedScene = Scene{.rootNode = rootNode};
    ChangeToScene(loadedScene);
    return loadedScene;
}

namespace SceneNodeHelper {
Transform2DComponent GetCombinedParentsTransforms(SceneManager *sceneManager, ComponentManager *componentManager, Entity entity) {
    SceneNode sceneNode = sceneManager->GetEntitySceneNode(entity);
    Transform2DComponent combinedTransform = Transform2DComponent{};
    Entity currentParent = sceneNode.parent;
    while (currentParent != NULL_ENTITY) {
        SceneNode nodeParent = sceneManager->GetEntitySceneNode(currentParent);
        if (componentManager->HasComponent<Transform2DComponent>(nodeParent.entity)) {
            Transform2DComponent parentTransform = componentManager->GetComponent<Transform2DComponent>(nodeParent.entity);
            combinedTransform.position += parentTransform.position;
            combinedTransform.scale *= parentTransform.scale;
            combinedTransform.zIndex += parentTransform.zIndex;
        } else if (componentManager->HasComponent<Transform3DComponent>(nodeParent.entity)) {
            // TODO: implement...
        }
        currentParent = nodeParent.parent;
    }
    return combinedTransform;
}
}
