#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include <vector>
#include <map>

#include "scene.h"

#include "../utils/json_helper.h"
#include "../utils/json_file_helper.h"

#include "../ecs/entity/entity_manager.h"
#include "../asset_manager.h"
#include "../ecs/component/components/transform2D_component.h"
#include "../ecs/component/components/sprite_component.h"
#include "../animation/animation.h"
#include "../ecs/component/components/animated_sprite_component.h"
#include "../ecs/component/components/text_label_component.h"
#include "../ecs/component/components/collider_component.h"
#include "../ecs/component/components/scriptable_class_component.h"
#include "scene_context.h"
#include "../timer/timer_manager.h"
#include "../ecs/component/components/node_component.h"
#include "../ecs/node_type_helper.h"
#include "../ecs/component/components/transform3D_component.h"
#include "../ecs/component/components/texture_cube_component.h"
#include "../ecs/component/components/material_component.h"
#include "../ecs/component/components/light3D_component.h"

class SceneNodeJsonParser {
  private:
    EntityManager *entityManager = nullptr;
    ComponentManager *componentManager = nullptr;
    AssetManager *assetManager = nullptr;
    TimerManager *timerManager = nullptr;

    void ParseComponents(SceneNode &sceneNode, const nlohmann::json &nodeComponentJsonArray) {
        for (nlohmann::json nodeComponentJson : nodeComponentJsonArray) {
            nlohmann::json::iterator it = nodeComponentJson.begin();
            const std::string &nodeComponentType = it.key();
            nlohmann::json nodeComponentObjectJson = it.value();
            // TODO: Map to functions with keys
            if (nodeComponentType == "transform2D") {
                ParseTransform2DComponent(sceneNode, nodeComponentObjectJson);
            } else if (nodeComponentType == "timer") {
                ParseTimerComponent(sceneNode, nodeComponentObjectJson);
            } else if (nodeComponentType == "sprite") {
                ParseSpriteComponent(sceneNode, nodeComponentObjectJson);
            } else if (nodeComponentType == "animated_sprite") {
                ParseAnimatedSpriteComponent(sceneNode, nodeComponentObjectJson);
            } else if (nodeComponentType == "text_label") {
                ParseTextLabelComponent(sceneNode, nodeComponentObjectJson);
            } else if (nodeComponentType == "collider") {
                ParseColliderComponent(sceneNode, nodeComponentObjectJson);
            } else if (nodeComponentType == "transform3D") {
                ParseTransform3DComponent(sceneNode, nodeComponentObjectJson);
            } else if (nodeComponentType == "material") {
                ParseMaterialComponent(sceneNode, nodeComponentObjectJson);
            } else if (nodeComponentType == "texture_cube") {
                ParseTextureCubeComponent(sceneNode, nodeComponentObjectJson);
            } else if (nodeComponentType == "directional_light") {
                ParseDirectionalLightComponent(sceneNode, nodeComponentObjectJson);
            } else if (nodeComponentType == "point_light") {
                ParsePointLightComponent(sceneNode, nodeComponentObjectJson);
            } else if (nodeComponentType == "spot_light") {
                ParseSpotLightComponent(sceneNode, nodeComponentObjectJson);
            } else if (nodeComponentType == "scriptable_class") {
                ParseScriptableClassComponent(sceneNode, nodeComponentObjectJson);
            }
        }
    }

    void ParseTransform2DComponent(SceneNode &sceneNode, const nlohmann::json &nodeComponentObjectJson) {
        nlohmann::json nodeTransform2DPosition = JsonHelper::Get<nlohmann::json>(nodeComponentObjectJson, "position");
        nlohmann::json nodeTransform2DScale = JsonHelper::Get<nlohmann::json>(nodeComponentObjectJson, "scale");
        const Vector2 nodePosition = Vector2(
                                         JsonHelper::Get<float>(nodeTransform2DPosition, "x"),
                                         JsonHelper::Get<float>(nodeTransform2DPosition, "y"));
        const Vector2 nodeScale = Vector2(
                                      JsonHelper::Get<float>(nodeTransform2DScale, "x"),
                                      JsonHelper::Get<float>(nodeTransform2DScale, "y"));
        const float nodeRotation = JsonHelper::Get<float>(nodeComponentObjectJson, "rotation");
        const int nodeZIndex = JsonHelper::Get<int>(nodeComponentObjectJson, "z_index");
        const bool nodeZIndexIsRelativeToParent = JsonHelper::Get<bool>(nodeComponentObjectJson, "z_index_relative_to_parent");
        const bool nodeIgnoreCamera = JsonHelper::Get<bool>(nodeComponentObjectJson, "ignore_camera");

        componentManager->AddComponent(sceneNode.entity, Transform2DComponent{
            .position = nodePosition,
            .scale = nodeScale,
            .rotation = nodeRotation,
            .zIndex = nodeZIndex,
            .isZIndexRelativeToParent = nodeZIndexIsRelativeToParent,
            .ignoreCamera = nodeIgnoreCamera
        });
        auto signature = entityManager->GetSignature(sceneNode.entity);
        signature.set(componentManager->GetComponentType<Transform2DComponent>(), true);
        entityManager->SetSignature(sceneNode.entity, signature);
    }

    void ParseTimerComponent(SceneNode &sceneNode, const nlohmann::json &nodeComponentObjectJson) {
        const Uint32 nodeWaitTimeInMilliseconds = (Uint32) JsonHelper::Get<float>(nodeComponentObjectJson, "wait_time") * 1000;
        const bool nodeLoops = JsonHelper::Get<bool>(nodeComponentObjectJson, "loops");
        componentManager->AddComponent(sceneNode.entity, TimerComponent{
            .timer = timerManager->GenerateTimer(sceneNode.entity, nodeWaitTimeInMilliseconds, nodeLoops)
        });
        auto signature = entityManager->GetSignature(sceneNode.entity);
        signature.set(componentManager->GetComponentType<TimerComponent>(), true);
        entityManager->SetSignature(sceneNode.entity, signature);
    }

    void ParseSpriteComponent(SceneNode &sceneNode, const nlohmann::json &nodeComponentObjectJson) {
        const std::string &nodeTexturePath = JsonHelper::Get<std::string>(nodeComponentObjectJson, "texture_path");
        nlohmann::json nodeDrawSourceJson = JsonHelper::Get<nlohmann::json>(nodeComponentObjectJson, "draw_source");
        const float nodeDrawSourceX = JsonHelper::Get<float>(nodeDrawSourceJson, "x");
        const float nodeDrawSourceY = JsonHelper::Get<float>(nodeDrawSourceJson, "y");
        const float nodeDrawSourceWidth = JsonHelper::Get<float>(nodeDrawSourceJson, "width");
        const float nodeDrawSourceHeight = JsonHelper::Get<float>(nodeDrawSourceJson, "height");
        const bool nodeFlipX = JsonHelper::Get<bool>(nodeComponentObjectJson, "flip_x");
        const bool nodeFlipY = JsonHelper::Get<bool>(nodeComponentObjectJson, "flip_x");
        nlohmann::json nodeModulateJson = JsonHelper::Get<nlohmann::json>(nodeComponentObjectJson, "modulate");
        const Color nodeModulate = Color(
                                       JsonHelper::Get<float>(nodeModulateJson, "red"),
                                       JsonHelper::Get<float>(nodeModulateJson, "green"),
                                       JsonHelper::Get<float>(nodeModulateJson, "blue"),
                                       JsonHelper::Get<float>(nodeModulateJson, "alpha")
                                   );

        componentManager->AddComponent(sceneNode.entity, SpriteComponent{
            .texture = nodeTexturePath.empty() ? nullptr : assetManager->GetTexture(nodeTexturePath),
            .drawSource = Rect2(nodeDrawSourceX, nodeDrawSourceY, nodeDrawSourceWidth, nodeDrawSourceHeight),
            .flipX = nodeFlipX,
            .flipY = nodeFlipY,
            .modulate = nodeModulate
        });
        auto signature = entityManager->GetSignature(sceneNode.entity);
        const bool isSpriteEnabled = !nodeTexturePath.empty();
        signature.set(componentManager->GetComponentType<SpriteComponent>(), isSpriteEnabled);
        entityManager->SetSignature(sceneNode.entity, signature);
    }

    void ParseAnimatedSpriteComponent(SceneNode &sceneNode, const nlohmann::json &nodeComponentObjectJson) {
        const std::string &nodeCurrentAnimationName = JsonHelper::Get<std::string>(nodeComponentObjectJson, "current_animation");
        const bool nodeIsPlaying = JsonHelper::Get<bool>(nodeComponentObjectJson, "is_playing");
        const bool nodeFlipX = JsonHelper::Get<bool>(nodeComponentObjectJson, "flip_x");
        const bool nodeFlipY = JsonHelper::Get<bool>(nodeComponentObjectJson, "flip_y");
        nlohmann::json nodeModulateJson = JsonHelper::Get<nlohmann::json>(nodeComponentObjectJson, "modulate");
        const Color nodeModulate = Color(
                                       JsonHelper::Get<float>(nodeModulateJson, "red"),
                                       JsonHelper::Get<float>(nodeModulateJson, "green"),
                                       JsonHelper::Get<float>(nodeModulateJson, "blue"),
                                       JsonHelper::Get<float>(nodeModulateJson, "alpha")
                                   );
        nlohmann::json nodeAnimationsJsonArray = JsonHelper::Get<nlohmann::json>(nodeComponentObjectJson, "animations");
        std::map<std::string, Animation> nodeAnimations;

        for (nlohmann::json nodeAnimationJson : nodeAnimationsJsonArray) {
            const std::string &nodeAnimationName = JsonHelper::Get<std::string>(nodeAnimationJson, "name");
            const int nodeAnimationSpeed = JsonHelper::Get<int>(nodeAnimationJson, "speed");
            nlohmann::json nodeAnimationFramesJsonArray = JsonHelper::Get<nlohmann::json>(nodeAnimationJson, "frames");
            std::map<unsigned int, AnimationFrame> animationFrames;
            for (nlohmann::json nodeAnimationFrameJson : nodeAnimationFramesJsonArray) {
                const int nodeAnimationFrameNumber = JsonHelper::Get<int>(nodeAnimationFrameJson, "frame");
                const std::string &nodeAnimationTexturePath = JsonHelper::Get<std::string>(nodeAnimationFrameJson, "texture_path");
                nlohmann::json nodeAnimationFrameDrawSourceJson = JsonHelper::Get<nlohmann::json>(nodeAnimationFrameJson, "draw_source");
                const float nodeAnimationFrameDrawSourceX = JsonHelper::Get<float>(nodeAnimationFrameDrawSourceJson, "x");
                const float nodeAnimationFrameDrawSourceY = JsonHelper::Get<float>(nodeAnimationFrameDrawSourceJson, "y");
                const float nodeAnimationFrameDrawSourceWidth = JsonHelper::Get<float>(nodeAnimationFrameDrawSourceJson, "width");
                const float nodeAnimationFrameDrawSourceHeight = JsonHelper::Get<float>(nodeAnimationFrameDrawSourceJson, "height");
                AnimationFrame nodeAnimationFrame = {
                    .texture = assetManager->GetTexture(nodeAnimationTexturePath),
                    .drawSource = Rect2(nodeAnimationFrameDrawSourceX, nodeAnimationFrameDrawSourceY, nodeAnimationFrameDrawSourceWidth, nodeAnimationFrameDrawSourceHeight),
                    .frame = nodeAnimationFrameNumber
                };
                animationFrames.emplace(nodeAnimationFrame.frame, nodeAnimationFrame);
            }

            Animation nodeAnimation = {
                .name = nodeAnimationName,
                .speed = nodeAnimationSpeed,
                .animationFrames = animationFrames,
                .frames = static_cast<unsigned int>(animationFrames.size())
            };
            nodeAnimations.emplace(nodeAnimation.name, nodeAnimation);
        }

        componentManager->AddComponent(sceneNode.entity, AnimatedSpriteComponent{
            .animations = nodeAnimations,
            .currentAnimation = !nodeCurrentAnimationName.empty() ? nodeAnimations[nodeCurrentAnimationName] : Animation{},
            .currentFrameIndex = 0,
            .isPlaying = nodeIsPlaying,
            .flipX = nodeFlipX,
            .flipY = nodeFlipY,
            .modulate = nodeModulate
        });
        auto signature = entityManager->GetSignature(sceneNode.entity);
        // Editor won't allow animations with empty textures
        const bool isAnimatedSpriteEnabled = !nodeAnimations.empty();
        signature.set(componentManager->GetComponentType<AnimatedSpriteComponent>(), isAnimatedSpriteEnabled);
        entityManager->SetSignature(sceneNode.entity, signature);
    }

    void ParseTextLabelComponent(SceneNode &sceneNode, const nlohmann::json &nodeComponentObjectJson) {
        const std::string &nodeText = JsonHelper::Get<std::string>(nodeComponentObjectJson, "text");
        const std::string &nodeFontUID = JsonHelper::Get<std::string>(nodeComponentObjectJson, "font_uid");
        nlohmann::json nodeColorJson = JsonHelper::Get<nlohmann::json>(nodeComponentObjectJson, "color");
        const Color nodeColor = Color(
                                    JsonHelper::Get<float>(nodeColorJson, "red"),
                                    JsonHelper::Get<float>(nodeColorJson, "green"),
                                    JsonHelper::Get<float>(nodeColorJson, "blue"),
                                    JsonHelper::Get<float>(nodeColorJson, "alpha")
                                );
        const bool nodeWordWrapped = JsonHelper::GetDefault<bool>(nodeComponentObjectJson, "word_wrap", false);
        const unsigned int nodeMaxCharactersPerLine = JsonHelper::GetDefault<unsigned int>(nodeComponentObjectJson, "max_characters_per_line", 999999999);
        const int nodeNewLinePadding = JsonHelper::GetDefault<int>(nodeComponentObjectJson, "new_line_padding", 2);

        componentManager->AddComponent(sceneNode.entity, TextLabelComponent{
            nodeText,
            nodeFontUID.empty() ? nullptr : assetManager->GetFont(nodeFontUID),
            nodeColor,
            nodeWordWrapped,
            nodeMaxCharactersPerLine,
            nodeNewLinePadding
        });
        auto signature = entityManager->GetSignature(sceneNode.entity);
        const bool isTextLabelEnabled = !nodeFontUID.empty();
        signature.set(componentManager->GetComponentType<TextLabelComponent>(), isTextLabelEnabled);
        entityManager->SetSignature(sceneNode.entity, signature);
    }

    void ParseColliderComponent(SceneNode &sceneNode, const nlohmann::json &nodeComponentObjectJson) {
        nlohmann::json nodeRectangleJson = JsonHelper::Get<nlohmann::json>(nodeComponentObjectJson, "rectangle");
        const float nodeX = JsonHelper::Get<float>(nodeRectangleJson, "x");
        const float nodeY = JsonHelper::Get<float>(nodeRectangleJson, "y");
        const float nodeWidth = JsonHelper::Get<float>(nodeRectangleJson, "width");
        const float nodeHeight = JsonHelper::Get<float>(nodeRectangleJson, "height");
        // Setting default collider color
        nlohmann::json defaultColor;
        defaultColor["red"] = DEFAULT_COLLIDER_COMPONENT_COLOR.r;
        defaultColor["green"] = DEFAULT_COLLIDER_COMPONENT_COLOR.g;
        defaultColor["blue"] = DEFAULT_COLLIDER_COMPONENT_COLOR.b;
        defaultColor["alpha"] = DEFAULT_COLLIDER_COMPONENT_COLOR.a;
        nlohmann::json nodeColor = JsonHelper::GetDefault<nlohmann::json>(nodeRectangleJson, "color", defaultColor);
        Color colliderColor = Color(
                                  JsonHelper::Get<float>(nodeColor, "red"),
                                  JsonHelper::Get<float>(nodeColor, "green"),
                                  JsonHelper::Get<float>(nodeColor, "blue"),
                                  JsonHelper::Get<float>(nodeColor, "alpha")
                              );

        ColliderComponent colliderComponent = {
            Rect2(nodeX, nodeY, nodeWidth, nodeHeight),
            { sceneNode.entity },
            colliderColor
        };
        componentManager->AddComponent(sceneNode.entity, colliderComponent);
        auto signature = entityManager->GetSignature(sceneNode.entity);
        signature.set(componentManager->GetComponentType<ColliderComponent>(), true);
        entityManager->SetSignature(sceneNode.entity, signature);
    }

    void ParseTransform3DComponent(SceneNode &sceneNode, const nlohmann::json &nodeComponentObjectJson) {
        nlohmann::json positionJson = JsonHelper::Get<nlohmann::json>(nodeComponentObjectJson, "position");
        Vector3 nodePosition = Vector3(
                                   JsonHelper::Get<float>(positionJson, "x"),
                                   JsonHelper::Get<float>(positionJson, "y"),
                                   JsonHelper::Get<float>(positionJson, "z")
                               );
        nlohmann::json scaleJson = JsonHelper::Get<nlohmann::json>(nodeComponentObjectJson, "scale");
        Vector3 nodeScale = Vector3(
                                JsonHelper::Get<float>(scaleJson, "x"),
                                JsonHelper::Get<float>(scaleJson, "y"),
                                JsonHelper::Get<float>(scaleJson, "z")
                            );
        const float nodeRotation = JsonHelper::Get<float>(nodeComponentObjectJson, "rotation");
        nlohmann::json rotationAxisJson = JsonHelper::Get<nlohmann::json>(nodeComponentObjectJson, "rotation_axis");
        Vector3 nodeRotationAxis = Vector3(
                                       JsonHelper::Get<float>(rotationAxisJson, "x"),
                                       JsonHelper::Get<float>(rotationAxisJson, "y"),
                                       JsonHelper::Get<float>(rotationAxisJson, "z")
                                   );
        componentManager->AddComponent(sceneNode.entity, Transform3DComponent{
            .position = nodePosition,
            .scale = nodeScale,
            .rotationAngleInDegrees = nodeRotation,
            .rotationAxisInDegrees = nodeRotationAxis
        });
        auto signature = entityManager->GetSignature(sceneNode.entity);
        signature.set(componentManager->GetComponentType<Transform3DComponent>(), true);
        entityManager->SetSignature(sceneNode.entity, signature);
    }

    void ParseMaterialComponent(SceneNode &sceneNode, const nlohmann::json &nodeComponentObjectJson) {
        nlohmann::json ambientJson = JsonHelper::Get<nlohmann::json>(nodeComponentObjectJson, "ambient");
        Vector3 nodeAmbient = Vector3(
                                  JsonHelper::Get<float>(ambientJson, "x"),
                                  JsonHelper::Get<float>(ambientJson, "y"),
                                  JsonHelper::Get<float>(ambientJson, "z")
                              );
        nlohmann::json diffuseJson = JsonHelper::Get<nlohmann::json>(nodeComponentObjectJson, "diffuse");
        Vector3 nodeDiffuse = Vector3(
                                  JsonHelper::Get<float>(diffuseJson, "x"),
                                  JsonHelper::Get<float>(diffuseJson, "y"),
                                  JsonHelper::Get<float>(diffuseJson, "z")
                              );
        nlohmann::json specularJson = JsonHelper::Get<nlohmann::json>(nodeComponentObjectJson, "specular");
        Vector3 nodeSpecular = Vector3(
                                   JsonHelper::Get<float>(specularJson, "x"),
                                   JsonHelper::Get<float>(specularJson, "y"),
                                   JsonHelper::Get<float>(specularJson, "z")
                               );
        const float nodeShininess = JsonHelper::Get<float>(nodeComponentObjectJson, "shininess");
        const std::string &nodeDiffuseMapTexturePath = JsonHelper::Get<std::string>(nodeComponentObjectJson, "diffuse_map_texture_path");
        const std::string &nodeSpecularMapTexturePath = JsonHelper::Get<std::string>(nodeComponentObjectJson, "specular_map_texture_path");

        componentManager->AddComponent(sceneNode.entity, MaterialComponent{
            .ambient = nodeAmbient,
            .diffuse = nodeDiffuse,
            .specular = nodeSpecular,
            .shininess = nodeShininess,
            .diffuseMap = nodeDiffuseMapTexturePath.empty() ? nullptr : assetManager->GetTexture(nodeDiffuseMapTexturePath),
            .specularMap = nodeSpecularMapTexturePath.empty() ? nullptr : assetManager->GetTexture(nodeSpecularMapTexturePath)
        });
        auto signature = entityManager->GetSignature(sceneNode.entity);
        signature.set(componentManager->GetComponentType<MaterialComponent>(), true);
        entityManager->SetSignature(sceneNode.entity, signature);
    }

    void ParseTextureCubeComponent(SceneNode &sceneNode, const nlohmann::json &nodeComponentObjectJson) {
        componentManager->AddComponent(sceneNode.entity, TextureCubeComponent{});
        auto signature = entityManager->GetSignature(sceneNode.entity);
        signature.set(componentManager->GetComponentType<TextureCubeComponent>(), true);
        entityManager->SetSignature(sceneNode.entity, signature);
    }

    void ParseDirectionalLightComponent(SceneNode &sceneNode, const nlohmann::json &nodeComponentObjectJson) {
        nlohmann::json directionJson = JsonHelper::Get<nlohmann::json>(nodeComponentObjectJson, "direction");
        Vector3 nodeDirection = Vector3(
                                    JsonHelper::Get<float>(directionJson, "x"),
                                    JsonHelper::Get<float>(directionJson, "y"),
                                    JsonHelper::Get<float>(directionJson, "z")
                                );

        componentManager->AddComponent(sceneNode.entity, DirectionalLightComponent{.direction = nodeDirection});
        auto signature = entityManager->GetSignature(sceneNode.entity);
        signature.set(componentManager->GetComponentType<DirectionalLightComponent>(), true);
        entityManager->SetSignature(sceneNode.entity, signature);
    }

    void ParsePointLightComponent(SceneNode &sceneNode, const nlohmann::json &nodeComponentObjectJson) {
        const float nodeLinear = JsonHelper::Get<float>(nodeComponentObjectJson, "linear");
        const float nodeQuadratic = JsonHelper::Get<float>(nodeComponentObjectJson, "quadratic");
        const float nodeConstant = JsonHelper::Get<float>(nodeComponentObjectJson, "constant");

        componentManager->AddComponent(sceneNode.entity, PointLightComponent{
            .linear = nodeLinear,
            .quadratic = nodeQuadratic,
            .constant = nodeConstant
        });
        auto signature = entityManager->GetSignature(sceneNode.entity);
        signature.set(componentManager->GetComponentType<PointLightComponent>(), true);
        entityManager->SetSignature(sceneNode.entity, signature);
    }

    void ParseSpotLightComponent(SceneNode &sceneNode, const nlohmann::json &nodeComponentObjectJson) {
        nlohmann::json directionJson = JsonHelper::Get<nlohmann::json>(nodeComponentObjectJson, "direction");
        Vector3 nodeDirection = Vector3(
                                    JsonHelper::Get<float>(directionJson, "x"),
                                    JsonHelper::Get<float>(directionJson, "y"),
                                    JsonHelper::Get<float>(directionJson, "z")
                                );
        const bool nodeIsAttachedToCamera = JsonHelper::Get<bool>(nodeComponentObjectJson, "is_attached_to_camera");
        const float nodeLinear = JsonHelper::Get<float>(nodeComponentObjectJson, "linear");
        const float nodeQuadratic = JsonHelper::Get<float>(nodeComponentObjectJson, "quadratic");
        const float nodeConstant = JsonHelper::Get<float>(nodeComponentObjectJson, "constant");
        const float nodeCutoff = JsonHelper::Get<float>(nodeComponentObjectJson, "cutoff");
        const float nodeOuterCutoff = JsonHelper::Get<float>(nodeComponentObjectJson, "outer_cutoff");

        componentManager->AddComponent(sceneNode.entity, SpotLightComponent{
            .direction = nodeDirection,
            .isAttachedToCamera = nodeIsAttachedToCamera,
            .cutoffInDegrees = nodeCutoff,
            .outerCutoffInDegrees = nodeOuterCutoff,
            .linear = nodeLinear,
            .quadratic = nodeQuadratic,
            .constant = nodeConstant
        });
        auto signature = entityManager->GetSignature(sceneNode.entity);
        signature.set(componentManager->GetComponentType<SpotLightComponent>(), true);
        entityManager->SetSignature(sceneNode.entity, signature);
    }

    void ParseScriptableClassComponent(SceneNode &sceneNode, const nlohmann::json &nodeComponentObjectJson) {
        const std::string &nodeClassPath = JsonHelper::Get<std::string>(nodeComponentObjectJson, "class_path");
        const std::string &nodeClassName = JsonHelper::Get<std::string>(nodeComponentObjectJson, "class_name");


        componentManager->AddComponent(sceneNode.entity, ScriptableClassComponent{
            .classPath = nodeClassPath,
            .className = nodeClassName
        });
        auto signature = entityManager->GetSignature(sceneNode.entity);
        // Editor will validate the scriptable component is valid
        signature.set(componentManager->GetComponentType<ScriptableClassComponent>(), true);
        entityManager->SetSignature(sceneNode.entity, signature);
    }
  public:
    SceneNodeJsonParser() = default;
    SceneNodeJsonParser(EntityManager *entityM, ComponentManager *componentM, AssetManager *assetM, TimerManager *timerM)
        : entityManager(entityM), componentManager(componentM), assetManager(assetM), timerManager(timerM) {}

    SceneNode ParseSceneJson(nlohmann::json nodeJson, bool isRoot) {
        SceneNode sceneNode;
        if (isRoot) {
            sceneNode = {entityManager->CreateEntity()};
        } else {
            sceneNode = {entityManager->CreateEntity(), JsonHelper::Get<unsigned int>(nodeJson, "parent_entity_id")};
        }

        const std::string &nodeName = JsonHelper::Get<std::string>(nodeJson, "name");
        const std::string &nodeType = JsonHelper::Get<std::string>(nodeJson, "type");
        nlohmann::json nodeTagsJsonArray = JsonHelper::Get<nlohmann::json>(nodeJson, "tags");
        const std::string &nodeExternalSceneSource = JsonHelper::Get<std::string>(nodeJson, "external_scene_source");
        nlohmann::json nodeComponentJsonArray = JsonHelper::Get<nlohmann::json>(nodeJson, "components");
        nlohmann::json nodeChildrenJsonArray = JsonHelper::Get<nlohmann::json>(nodeJson, "children");

        // Configure node type component
        std::vector<std::string> nodeTags;
        for (const std::string &nodeTag : nodeTagsJsonArray) {
            nodeTags.emplace_back(nodeTag);
        }
        componentManager->AddComponent(sceneNode.entity, NodeComponent{
            .type = NodeTypeHelper::GetNodeTypeInt(nodeType),
            .name = nodeName,
            .tags = nodeTags
        });

        // Rest of components
        ParseComponents(sceneNode, nodeComponentJsonArray);

        for (nlohmann::json nodeChildJson : nodeChildrenJsonArray) {
            nodeChildJson["parent_entity_id"] = sceneNode.entity;
            SceneNode childNode = ParseSceneJson(nodeChildJson, false);
            sceneNode.children.emplace_back(childNode);
        }

        return sceneNode;
    }
};

class SceneManager {
  private:
    std::map<Entity, Scene> entityToMainScenesMap; // Holds singleton scene and current scene
    std::map<Entity, SceneNode> entityToSceneNodeMap;
    std::vector<Entity> entitiesRecentlyRemoved;
    SceneNodeJsonParser sceneNodeJsonParser;

    Scene currentScene;
    SceneContext *sceneContext = nullptr;
    EntityManager *entityManager = nullptr;
    ComponentManager *componentManager = nullptr;
    AssetManager *assetManager = nullptr;
    TimerManager *timerManager = nullptr;
    ArchiveLoader *archiveLoader = nullptr;

  public:
    SceneManager(SceneContext *vSceneContext, EntityManager *vEntityManager, ComponentManager *vComponentManager, AssetManager *vAssetManager) :
        sceneContext(vSceneContext), entityManager(vEntityManager), componentManager(vComponentManager), assetManager(vAssetManager) {
        timerManager = TimerManager::GetInstance();
        archiveLoader = ArchiveLoader::GetInstance();
        sceneNodeJsonParser = SceneNodeJsonParser(entityManager, componentManager, assetManager, timerManager);
    }

    Scene GetCurrentScene() {
        return currentScene;
    }

    SceneNode GetEntitySceneNode(Entity entity) {
        assert(HasEntitySceneNode(entity) && "Tried to get scene node that doesn't exist!");
        return entityToSceneNodeMap[entity];
    }

    bool HasEntitySceneNode(Entity entity) {
        return entityToSceneNodeMap.count(entity) > 0;
    }

    void AddSingletonScene(Entity singletonEntity) {
        SceneNode sceneNode = SceneNode{.entity = singletonEntity};
        Scene scene = Scene{.rootNode = sceneNode};
        entityToMainScenesMap.emplace(singletonEntity, scene);
    }

    void ChangeToScene(Scene scene) {
        currentScene = scene;
        sceneContext->currentSceneEntity = currentScene.rootNode.entity;
        entityToMainScenesMap.emplace(currentScene.rootNode.entity, currentScene);
        AddChild(NO_ENTITY, currentScene.rootNode.entity);
    }

    void AddChild(Entity parent, Entity child) {
        SceneNode childNode = SceneNode{.entity = child, .parent = parent};
        if (parent != NO_ENTITY) {
            assert((entityToSceneNodeMap.count(parent) > 0) && "Parent scene node doesn't exist!");
            SceneNode parentNode = entityToSceneNodeMap[parent];
            parentNode.children.emplace_back(childNode);
            entityToSceneNodeMap[parent] = parentNode;
            if (parentNode.entity == currentScene.rootNode.entity) {
                currentScene.rootNode.children.emplace_back(childNode);
            }
        }
//        assert((entityToSceneNodeMap.count(child) <= 0) && "Child already exists!");
        entityToSceneNodeMap.emplace(childNode.entity, childNode);
    }

    std::vector<Entity> GetAllChildEntities(Entity entity) {
        std::vector<Entity> childrenEntities;
        SceneNode parentNode = GetEntitySceneNode(entity);
        for (SceneNode childNode : parentNode.children) {
            if (IsEntityInScene(childNode.entity)) {
                childrenEntities.emplace_back(childNode.entity);
            }
        }
        return childrenEntities;
    }

    Entity GetParent(Entity entity) {
        if (IsEntityInScene(entity)) {
            SceneNode sceneNode = entityToSceneNodeMap[entity];
            return sceneNode.parent;
        }
        return NO_ENTITY;
    }

    void RemoveNode(SceneNode sceneNode) {
        entityToSceneNodeMap.erase(sceneNode.entity);
        entityToMainScenesMap.erase(sceneNode.entity);
        entitiesRecentlyRemoved.emplace_back(sceneNode.entity);
        for (SceneNode childNode : sceneNode.children) {
            RemoveNode(childNode);
        }
    }

    void RemoveNode(Entity entity) {
        if (entityToSceneNodeMap.count(entity) > 0) {
            RemoveNode(entityToSceneNodeMap[entity]);
        } else {
            Logger::GetInstance()->Warn("Tried to remove non existent entity");
        }
    }

    std::vector<Entity> FlushRemovedEntities() {
        std::vector<Entity> removedEntitiesCopy = entitiesRecentlyRemoved;
        entitiesRecentlyRemoved.clear();
        return removedEntitiesCopy;
    }

    bool IsEntityInScene(Entity entity) {
        return entityToSceneNodeMap.count(entity) > 0;
    }

    Scene LoadSceneFromFile(const std::string &filePath) {
        nlohmann::json sceneJson = JsonFileHelper::LoadJsonFile(filePath);
        SceneNode rootNode = sceneNodeJsonParser.ParseSceneJson(sceneJson, true);
        Scene loadedScene = Scene{.rootNode = rootNode};
        ChangeToScene(loadedScene);
        return loadedScene;
    }

    Scene LoadSceneFromMemory(const std::string &filePath) {
        const std::string &sceneArchiveJsonString = archiveLoader->LoadAsString(filePath);
        nlohmann::json sceneJson = JsonFileHelper::ConvertStringToJson(sceneArchiveJsonString);
        SceneNode rootNode = sceneNodeJsonParser.ParseSceneJson(sceneJson, true);
        Scene loadedScene = Scene{.rootNode = rootNode};
        ChangeToScene(loadedScene);
        return loadedScene;
    }
};

class SceneNodeHelper {
  public:
    static Transform2DComponent GetCombinedParentsTransforms(SceneManager *sceneManager, ComponentManager *componentManager, Entity entity) {
        SceneNode sceneNode = sceneManager->GetEntitySceneNode(entity);
        Transform2DComponent combinedTransform = Transform2DComponent{};
        Entity currentParent = sceneNode.parent;
        while (currentParent != NO_ENTITY) {
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
};

#endif //SCENE_MANAGER_H
