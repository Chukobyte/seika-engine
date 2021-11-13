#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include <vector>
#include <map>

#include "scene.h"

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
        nlohmann::json nodeTransform2DPosition = nodeComponentObjectJson["position"].get<nlohmann::json>();
        nlohmann::json nodeTransform2DScale = nodeComponentObjectJson["scale"].get<nlohmann::json>();
        const Vector2 nodePosition = Vector2(nodeTransform2DPosition["x"].get<float>(),nodeTransform2DPosition["y"].get<float>());
        const Vector2 nodeScale = Vector2(nodeTransform2DScale["x"].get<float>(), nodeTransform2DScale["y"].get<float>());
        const float nodeRotation = nodeComponentObjectJson["rotation"];
        const int nodeZIndex = nodeComponentObjectJson["z_index"].get<int>();
        const bool nodeZIndexIsRelativeToParent = nodeComponentObjectJson["z_index_relative_to_parent"].get<bool>();
        const bool nodeIgnoreCamera = nodeComponentObjectJson["ignore_camera"].get<bool>();

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
        const Uint32 nodeWaitTimeInMilliseconds = (Uint32) nodeComponentObjectJson["wait_time"].get<float>() * 1000;
        const bool nodeLoops = nodeComponentObjectJson["loops"].get<bool>();
        componentManager->AddComponent(sceneNode.entity, TimerComponent{
            .timer = timerManager->GenerateTimer(sceneNode.entity, nodeWaitTimeInMilliseconds, nodeLoops)
        });
        auto signature = entityManager->GetSignature(sceneNode.entity);
        signature.set(componentManager->GetComponentType<TimerComponent>(), true);
        entityManager->SetSignature(sceneNode.entity, signature);
    }

    void ParseSpriteComponent(SceneNode &sceneNode, const nlohmann::json &nodeComponentObjectJson) {
        const std::string &nodeTexturePath = nodeComponentObjectJson["texture_path"].get<std::string>();
        nlohmann::json nodeDrawSourceJson = nodeComponentObjectJson["draw_source"].get<nlohmann::json>();
        const float nodeDrawSourceX = nodeDrawSourceJson["x"].get<float>();
        const float nodeDrawSourceY = nodeDrawSourceJson["y"].get<float>();
        const float nodeDrawSourceWidth = nodeDrawSourceJson["width"].get<float>();
        const float nodeDrawSourceHeight = nodeDrawSourceJson["height"].get<float>();
        const bool nodeFlipX = nodeComponentObjectJson["flip_x"].get<bool>();
        const bool nodeFlipY = nodeComponentObjectJson["flip_y"].get<bool>();
        const Color nodeModulate = Color(
                                       nodeComponentObjectJson["modulate"]["red"].get<float>(),
                                       nodeComponentObjectJson["modulate"]["green"].get<float>(),
                                       nodeComponentObjectJson["modulate"]["blue"].get<float>(),
                                       nodeComponentObjectJson["modulate"]["alpha"].get<float>()
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
        const std::string &nodeCurrentAnimationName = nodeComponentObjectJson["current_animation"].get<std::string>();
        const bool nodeIsPlaying = nodeComponentObjectJson["is_playing"].get<bool>();
        const bool nodeFlipX = nodeComponentObjectJson["flip_x"].get<bool>();
        const bool nodeFlipY = nodeComponentObjectJson["flip_y"].get<bool>();
        const Color nodeModulate = Color(
                                       nodeComponentObjectJson["modulate"]["red"].get<float>(),
                                       nodeComponentObjectJson["modulate"]["green"].get<float>(),
                                       nodeComponentObjectJson["modulate"]["blue"].get<float>(),
                                       nodeComponentObjectJson["modulate"]["alpha"].get<float>()
                                   );
        nlohmann::json nodeAnimationsJsonArray = nodeComponentObjectJson["animations"].get<nlohmann::json>();
        std::map<std::string, Animation> nodeAnimations;

        for (nlohmann::json nodeAnimationJson : nodeAnimationsJsonArray) {
            const std::string &nodeAnimationName = nodeAnimationJson["name"].get<std::string>();
            const int nodeAnimationSpeed = nodeAnimationJson["speed"].get<int>();
            nlohmann::json nodeAnimationFramesJsonArray = nodeAnimationJson["frames"].get<nlohmann::json>();
            std::map<unsigned int, AnimationFrame> animationFrames;
            for (nlohmann::json nodeAnimationFrameJson : nodeAnimationFramesJsonArray) {
                const int nodeAnimationFrameNumber = nodeAnimationFrameJson["frame"].get<int>();
                const std::string &nodeAnimationTexturePath = nodeAnimationFrameJson["texture_path"].get<std::string>();
                nlohmann::json nodeAnimationFrameDrawSourceJson = nodeAnimationFrameJson["draw_source"].get<nlohmann::json>();
                const float nodeAnimationFrameDrawSourceX = nodeAnimationFrameDrawSourceJson["x"].get<float>();
                const float nodeAnimationFrameDrawSourceY = nodeAnimationFrameDrawSourceJson["y"].get<float>();
                const float nodeAnimationFrameDrawSourceWidth = nodeAnimationFrameDrawSourceJson["width"].get<float>();
                const float nodeAnimationFrameDrawSourceHeight = nodeAnimationFrameDrawSourceJson["height"].get<float>();
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
        const std::string &nodeText = nodeComponentObjectJson["text"].get<std::string>();
        const std::string &nodeFontUID = nodeComponentObjectJson["font_uid"].get<std::string>();
        nlohmann::json nodeColorJson = nodeComponentObjectJson["color"].get<nlohmann::json>();
        const Color nodeColor = Color(
                                    nodeColorJson["red"].get<float>(),
                                    nodeColorJson["green"].get<float>(),
                                    nodeColorJson["blue"].get<float>(),
                                    nodeColorJson["alpha"].get<float>()
                                );

        componentManager->AddComponent(sceneNode.entity, TextLabelComponent{
            .text = nodeText,
            .font = nodeFontUID.empty() ? nullptr : assetManager->GetFont(nodeFontUID),
            .color = nodeColor
        });
        auto signature = entityManager->GetSignature(sceneNode.entity);
        const bool isTextLabelEnabled = !nodeFontUID.empty();
        signature.set(componentManager->GetComponentType<TextLabelComponent>(), isTextLabelEnabled);
        entityManager->SetSignature(sceneNode.entity, signature);
    }

    void ParseColliderComponent(SceneNode &sceneNode, const nlohmann::json &nodeComponentObjectJson) {
        nlohmann::json nodeRectangleJson = nodeComponentObjectJson["rectangle"].get<nlohmann::json>();
        const float nodeX = nodeRectangleJson["x"].get<float>();
        const float nodeY = nodeRectangleJson["y"].get<float>();
        const float nodeWidth = nodeRectangleJson["width"].get<float>();
        const float nodeHeight = nodeRectangleJson["height"].get<float>();

        ColliderComponent colliderComponent = ColliderComponent{
            .collider = Rect2(nodeX, nodeY, nodeWidth, nodeHeight),
            .collisionExceptions = { sceneNode.entity }
        };
        if (nodeComponentObjectJson.contains("color")) {
            const float nodeColorRed = nodeComponentObjectJson["color"]["red"].get<float>();
            const float nodeColorGreen = nodeComponentObjectJson["color"]["green"].get<float>();
            const float nodeColorBlue = nodeComponentObjectJson["color"]["blue"].get<float>();
            const float nodeColorAlpha = nodeComponentObjectJson["color"]["alpha"].get<float>();
            colliderComponent.color = Color(nodeColorRed, nodeColorGreen, nodeColorBlue, nodeColorAlpha);
        }
        componentManager->AddComponent(sceneNode.entity, colliderComponent);
        auto signature = entityManager->GetSignature(sceneNode.entity);
        signature.set(componentManager->GetComponentType<ColliderComponent>(), true);
        entityManager->SetSignature(sceneNode.entity, signature);
    }

    void ParseTransform3DComponent(SceneNode &sceneNode, const nlohmann::json &nodeComponentObjectJson) {
        Vector3 nodePosition = Vector3(
                                   nodeComponentObjectJson["position"]["x"].get<float>(),
                                   nodeComponentObjectJson["position"]["y"].get<float>(),
                                   nodeComponentObjectJson["position"]["z"].get<float>()
                               );
        Vector3 nodeScale = Vector3(
                                nodeComponentObjectJson["scale"]["x"].get<float>(),
                                nodeComponentObjectJson["scale"]["y"].get<float>(),
                                nodeComponentObjectJson["scale"]["z"].get<float>()
                            );
        const float nodeRotation = nodeComponentObjectJson["rotation"].get<float>();
        Vector3 nodeRotationAxis = Vector3(
                                       nodeComponentObjectJson["scale"]["x"].get<float>(),
                                       nodeComponentObjectJson["scale"]["y"].get<float>(),
                                       nodeComponentObjectJson["scale"]["z"].get<float>()
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
        Vector3 nodeAmbient = Vector3(
                                  nodeComponentObjectJson["ambient"]["x"].get<float>(),
                                  nodeComponentObjectJson["ambient"]["y"].get<float>(),
                                  nodeComponentObjectJson["ambient"]["z"].get<float>()
                              );
        Vector3 nodeDiffuse = Vector3(
                                  nodeComponentObjectJson["diffuse"]["x"].get<float>(),
                                  nodeComponentObjectJson["diffuse"]["y"].get<float>(),
                                  nodeComponentObjectJson["diffuse"]["z"].get<float>()
                              );
        Vector3 nodeSpecular = Vector3(
                                   nodeComponentObjectJson["specular"]["x"].get<float>(),
                                   nodeComponentObjectJson["specular"]["y"].get<float>(),
                                   nodeComponentObjectJson["specular"]["z"].get<float>()
                               );
        float nodeShininess = nodeComponentObjectJson["shininess"].get<float>();
        const std::string &nodeDiffuseMapTexturePath = nodeComponentObjectJson["diffuse_map_texture_path"].get<std::string>();
        const std::string &nodeSpecularMapTexturePath = nodeComponentObjectJson["specular_map_texture_path"].get<std::string>();
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
        Vector3 nodeDirection = Vector3(
                                    nodeComponentObjectJson["direction"]["x"].get<float>(),
                                    nodeComponentObjectJson["direction"]["y"].get<float>(),
                                    nodeComponentObjectJson["direction"]["z"].get<float>()
                                );

        componentManager->AddComponent(sceneNode.entity, DirectionalLightComponent{.direction = nodeDirection});
        auto signature = entityManager->GetSignature(sceneNode.entity);
        signature.set(componentManager->GetComponentType<DirectionalLightComponent>(), true);
        entityManager->SetSignature(sceneNode.entity, signature);
    }

    void ParsePointLightComponent(SceneNode &sceneNode, const nlohmann::json &nodeComponentObjectJson) {
        const float nodeLinear = nodeComponentObjectJson["linear"].get<float>();
        const float nodeQuadratic = nodeComponentObjectJson["quadratic"].get<float>();
        const float nodeConstant = nodeComponentObjectJson["constant"].get<float>();

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
        Vector3 nodeDirection = Vector3(
                                    nodeComponentObjectJson["direction"]["x"].get<float>(),
                                    nodeComponentObjectJson["direction"]["y"].get<float>(),
                                    nodeComponentObjectJson["direction"]["z"].get<float>()
                                );
        const bool nodeIsAttachedToCamera = nodeComponentObjectJson["is_attached_to_camera"].get<bool>();
        const float nodeLinear = nodeComponentObjectJson["linear"].get<float>();
        const float nodeQuadratic = nodeComponentObjectJson["quadratic"].get<float>();
        const float nodeConstant = nodeComponentObjectJson["constant"].get<float>();
        const float nodeCutoff = nodeComponentObjectJson["cutoff"].get<float>();
        const float nodeOuterCutoff = nodeComponentObjectJson["outer_cutoff"].get<float>();

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
        const std::string &nodeClassPath = nodeComponentObjectJson["class_path"].get<std::string>();
        const std::string &nodeClassName = nodeComponentObjectJson["class_name"].get<std::string>();

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
            sceneNode = SceneNode{.entity = entityManager->CreateEntity()};
        } else {
            sceneNode = SceneNode{.entity = entityManager->CreateEntity(), .parent = nodeJson["parent_entity_id"].get<unsigned int>()};
        }

        const std::string &nodeName = nodeJson["name"].get<std::string>();
        const std::string &nodeType = nodeJson["type"].get<std::string>();
        nlohmann::json nodeTagsJsonArray = nodeJson["tags"].get<nlohmann::json>();
        const std::string &nodeExternalSceneSource = nodeJson["external_scene_source"].get<std::string>();
        nlohmann::json nodeComponentJsonArray = nodeJson["components"].get<nlohmann::json>();
        nlohmann::json nodeChildrenJsonArray = nodeJson["children"].get<nlohmann::json>();

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
