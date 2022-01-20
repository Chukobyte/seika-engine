#pragma once

#include <vector>
#include <map>

#include "scene.h"

#include "../utils/json_helper.h"
#include "../utils/json_file_helper.h"

#include "../ecs/entity/entity_manager.h"
#include "../asset_manager.h"
#include "scene_context.h"
#include "../timer/timer_manager.h"
#include "../animation/animation.h"
#include "../ecs/node_type_helper.h"
#include "scene_node_loader.h"

// TODO: Separate SceneNodeJsonParser into its own file...
class SceneManager {
  private:
    std::map<Entity, Scene> entityToMainScenesMap; // Holds singleton scene and current scene
    std::map<Entity, SceneNode> entityToSceneNodeMap;
    std::vector<Entity> entitiesRecentlyRemoved;
    SceneNodeLoader sceneNodeLoader;

    Scene currentScene;
    SceneContext *sceneContext = nullptr;
    EntityManager *entityManager = nullptr;
    ComponentManager *componentManager = nullptr;
    AssetManager *assetManager = nullptr;
    TimerManager *timerManager = nullptr;
    ArchiveLoader *archiveLoader = nullptr;

  public:
    SceneManager(SceneContext *vSceneContext, EntityManager *vEntityManager, ComponentManager *vComponentManager, AssetManager *vAssetManager);
    Scene GetCurrentScene();
    SceneNode GetEntitySceneNode(Entity entity);
    bool HasEntitySceneNode(Entity entity) const;
    void ChangeToScene(Scene scene);
    void AddChild(Entity parent, Entity child);
    std::vector<Entity> GetAllChildEntities(Entity entity);
    Entity GetParent(Entity entity);
    void RemoveNode(SceneNode sceneNode);
    std::vector<Entity> FlushRemovedEntities();
    bool IsEntityInScene(Entity entity) const;
    Scene LoadSceneFromFile(const std::string &filePath);
    Scene LoadSceneFromMemory(const std::string &filePath);
};

namespace SceneNodeHelper {
Transform2DComponent GetCombinedParentsTransforms(SceneManager *sceneManager, ComponentManager *componentManager, Entity entity);
}
