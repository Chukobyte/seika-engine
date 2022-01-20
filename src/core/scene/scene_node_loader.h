#pragma once

#include "scene.h"

#include "../ecs/entity/entity_manager.h"
#include "../ecs/component/component_manager.h"
#include "../asset_manager.h"
#include "../timer/timer_manager.h"

class SceneNodeLoader {
  private:
    EntityManager *entityManager = nullptr;
    ComponentManager *componentManager = nullptr;
    AssetManager *assetManager = nullptr;
    TimerManager *timerManager = nullptr;

    void ParseComponents(SceneNode &sceneNode, const nlohmann::json &nodeComponentJsonArray, bool enabled);
    void ParseTransform2DComponent(SceneNode &sceneNode, const nlohmann::json &nodeComponentObjectJson, bool enabled);
    void ParseTimerComponent(SceneNode &sceneNode, const nlohmann::json &nodeComponentObjectJson, bool enabled);
    void ParseSpriteComponent(SceneNode &sceneNode, const nlohmann::json &nodeComponentObjectJson, bool enabled);
    void ParseAnimatedSpriteComponent(SceneNode &sceneNode, const nlohmann::json &nodeComponentObjectJson, bool enabled);
    void ParseTextLabelComponent(SceneNode &sceneNode, const nlohmann::json &nodeComponentObjectJson, bool enabled);
    void ParseColliderComponent(SceneNode &sceneNode, const nlohmann::json &nodeComponentObjectJson, bool enabled);
    void ParseTransform3DComponent(SceneNode &sceneNode, const nlohmann::json &nodeComponentObjectJson, bool enabled);
    void ParseMaterialComponent(SceneNode &sceneNode, const nlohmann::json &nodeComponentObjectJson, bool enabled);
    void ParseTextureCubeComponent(SceneNode &sceneNode, const nlohmann::json &nodeComponentObjectJson, bool enabled);
    void ParseDirectionalLightComponent(SceneNode &sceneNode, const nlohmann::json &nodeComponentObjectJson, bool enabled);
    void ParsePointLightComponent(SceneNode &sceneNode, const nlohmann::json &nodeComponentObjectJson, bool enabled);
    void ParseSpotLightComponent(SceneNode &sceneNode, const nlohmann::json &nodeComponentObjectJson, bool enabled);
    void ParseScriptableClassComponent(SceneNode &sceneNode, const nlohmann::json &nodeComponentObjectJson, bool enabled);

  public:
    SceneNodeLoader() = default;
    SceneNodeLoader(EntityManager *entityM, ComponentManager *componentM, AssetManager *assetM, TimerManager *timerM);
    SceneNode ParseSceneJson(nlohmann::json nodeJson, bool isRoot);
};
