#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <map>

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
#include "../ecs/component/components/node_component.h"
#include "../ecs/node_type_helper.h"
#include "../timer/timer_manager.h"

struct SceneNode {
    Entity entity = NO_ENTITY;
    Entity parent = NO_ENTITY;
    std::vector<SceneNode> children;
};

struct Scene {
    SceneNode rootNode;
};

class SceneManager {
  private:
    std::map<Entity, Scene> entityToMainScenesMap; // Holds singleton scene and current scene
    std::map<Entity, SceneNode> entityToSceneNodeMap;
    std::vector<Entity> entitiesRecentlyRemoved;

    Scene currentScene;
    SceneContext *sceneContext = nullptr;
    EntityManager *entityManager = nullptr;
    ComponentManager *componentManager = nullptr;
    AssetManager *assetManager = nullptr;
    TimerManager *timerManager = nullptr;

    SceneNode ParseSceneJson(nlohmann::json nodeJson, bool isRoot) {
        SceneNode sceneNode;
        if (isRoot) {
            sceneNode = SceneNode{.entity = entityManager->CreateEntity()};
        } else {
            sceneNode = SceneNode{.entity = entityManager->CreateEntity(), .parent = nodeJson["parent_entity_id"].get<unsigned int>()};
        }

        std::string nodeName = nodeJson["name"].get<std::string>();
        std::string nodeType = nodeJson["type"].get<std::string>();
        nlohmann::json nodeTagsJsonArray = nodeJson["tags"].get<nlohmann::json>();
        std::string nodeExternalSceneSource = nodeJson["external_scene_source"].get<std::string>();
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
        for (nlohmann::json nodeComponentJson : nodeComponentJsonArray) {
            nlohmann::json::iterator it = nodeComponentJson.begin();
            std::string nodeComponentType = it.key();
            nlohmann::json nodeComponentObjectJson = it.value();
            if (nodeComponentType == "transform2D") {
                nlohmann::json nodeTransform2DPosition = nodeComponentObjectJson["position"].get<nlohmann::json>();
                nlohmann::json nodeTransform2DScale = nodeComponentObjectJson["scale"].get<nlohmann::json>();
                Vector2 nodePosition = Vector2(nodeTransform2DPosition["x"].get<float>(),nodeTransform2DPosition["y"].get<float>());
                Vector2 nodeScale = Vector2(nodeTransform2DScale["x"].get<float>(), nodeTransform2DScale["y"].get<float>());
                float nodeRotation = nodeComponentObjectJson["rotation"];
                int nodeZIndex = nodeComponentObjectJson["z_index"].get<int>();
                bool nodeZIndexIsRelativeToParent = nodeComponentObjectJson["z_index_relative_to_parent"].get<bool>();
                bool nodeIgnoreCamera = nodeComponentObjectJson["ignore_camera"].get<bool>();

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
            } else if (nodeComponentType == "timer") {
                Uint32 nodeWaitTimeInMilliseconds = (Uint32) nodeComponentObjectJson["wait_time"].get<float>() * 1000;
                bool nodeLoops = nodeComponentObjectJson["loops"].get<bool>();
                componentManager->AddComponent(sceneNode.entity, TimerComponent{
                    .timer = timerManager->GenerateTimer(sceneNode.entity, nodeWaitTimeInMilliseconds, nodeLoops)
                });
            } else if (nodeComponentType == "sprite") {
                std::string nodeTexturePath = nodeComponentObjectJson["texture_path"].get<std::string>();
                nlohmann::json nodeDrawSourceJson = nodeComponentObjectJson["draw_source"].get<nlohmann::json>();
                float nodeDrawSourceX = nodeDrawSourceJson["x"].get<float>();
                float nodeDrawSourceY = nodeDrawSourceJson["y"].get<float>();
                float nodeDrawSourceWidth = nodeDrawSourceJson["width"].get<float>();
                float nodeDrawSourceHeight = nodeDrawSourceJson["height"].get<float>();
                bool nodeFlipX = nodeComponentObjectJson["flip_x"].get<bool>();
                bool nodeFlipY = nodeComponentObjectJson["flip_y"].get<bool>();

                componentManager->AddComponent(sceneNode.entity, SpriteComponent{
                    .texture = assetManager->GetTexture(nodeTexturePath),
                    .drawSource = Rect2(nodeDrawSourceX, nodeDrawSourceY, nodeDrawSourceWidth, nodeDrawSourceHeight),
                    .flipX = nodeFlipX,
                    .flipY = nodeFlipY
                });
                auto signature = entityManager->GetSignature(sceneNode.entity);
                signature.set(componentManager->GetComponentType<SpriteComponent>(), true);
                entityManager->SetSignature(sceneNode.entity, signature);
            } else if (nodeComponentType == "animated_sprite") {
                std::string nodeCurrentAnimationName = nodeComponentObjectJson["current_animation"].get<std::string>();
                bool nodeIsPlaying = nodeComponentObjectJson["is_playing"].get<bool>();
                bool nodeFlipX = nodeComponentObjectJson["flip_x"].get<bool>();
                bool nodeFlipY = nodeComponentObjectJson["flip_y"].get<bool>();
                nlohmann::json nodeAnimationsJsonArray = nodeComponentObjectJson["animations"].get<nlohmann::json>();
                std::map<std::string, Animation> nodeAnimations;

                for (nlohmann::json nodeAnimationJson : nodeAnimationsJsonArray) {
                    std::string nodeAnimationName = nodeAnimationJson["name"].get<std::string>();
                    int nodeAnimationSpeed = nodeAnimationJson["speed"].get<int>();
                    nlohmann::json nodeAnimationFramesJsonArray = nodeAnimationJson["frames"].get<nlohmann::json>();
                    std::map<unsigned int, AnimationFrame> animationFrames;
                    for (nlohmann::json nodeAnimationFrameJson : nodeAnimationFramesJsonArray) {
                        int nodeAnimationFrameNumber = nodeAnimationFrameJson["frame"].get<int>();
                        std::string nodeAnimationTexturePath = nodeAnimationFrameJson["texture_path"].get<std::string>();
                        nlohmann::json nodeAnimationFrameDrawSourceJson = nodeAnimationFrameJson["draw_source"].get<nlohmann::json>();
                        float nodeAnimationFrameDrawSourceX = nodeAnimationFrameDrawSourceJson["x"].get<float>();
                        float nodeAnimationFrameDrawSourceY = nodeAnimationFrameDrawSourceJson["y"].get<float>();
                        float nodeAnimationFrameDrawSourceWidth = nodeAnimationFrameDrawSourceJson["width"].get<float>();
                        float nodeAnimationFrameDrawSourceHeight = nodeAnimationFrameDrawSourceJson["height"].get<float>();
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
                    .flipY = nodeFlipY
                });
                auto signature = entityManager->GetSignature(sceneNode.entity);
                signature.set(componentManager->GetComponentType<AnimatedSpriteComponent>(), true);
                entityManager->SetSignature(sceneNode.entity, signature);
            } else if (nodeComponentType == "text_label") {
                std::string nodeText = nodeComponentObjectJson["text"].get<std::string>();
                std::string nodeFontPath = nodeComponentObjectJson["font_path"].get<std::string>();
                nlohmann::json nodeColorJson = nodeComponentObjectJson["color"].get<nlohmann::json>();
                Color nodeColor = Color(
                                      nodeColorJson["red"].get<float>(),
                                      nodeColorJson["green"].get<float>(),
                                      nodeColorJson["blue"].get<float>(),
                                      nodeColorJson["alpha"].get<float>()
                                  );

                componentManager->AddComponent(sceneNode.entity, TextLabelComponent{
                    .text = nodeText,
                    .font = assetManager->GetFont(nodeFontPath),
                    .color = nodeColor
                });
                auto signature = entityManager->GetSignature(sceneNode.entity);
                signature.set(componentManager->GetComponentType<TextLabelComponent>(), true);
                entityManager->SetSignature(sceneNode.entity, signature);
            } else if (nodeComponentType == "collider") {
                nlohmann::json nodeRectangleJson = nodeComponentObjectJson["rectangle"].get<nlohmann::json>();
                float nodeX = nodeRectangleJson["x"].get<float>();
                float nodeY = nodeRectangleJson["y"].get<float>();
                float nodeWidth = nodeRectangleJson["width"].get<float>();
                float nodeHeight = nodeRectangleJson["height"].get<float>();

                componentManager->AddComponent(sceneNode.entity, ColliderComponent{
                    .collider = Rect2(nodeX, nodeY, nodeWidth, nodeHeight)
                });
                auto signature = entityManager->GetSignature(sceneNode.entity);
                signature.set(componentManager->GetComponentType<ColliderComponent>(), true);
                entityManager->SetSignature(sceneNode.entity, signature);
            } else if (nodeComponentType == "scriptable_class") {
                std::string nodeClassPath = nodeComponentObjectJson["class_path"].get<std::string>();
                std::string nodeClassName = nodeComponentObjectJson["class_name"].get<std::string>();

                componentManager->AddComponent(sceneNode.entity, ScriptableClassComponent{
                    .classPath = nodeClassPath,
                    .className = nodeClassName
                });
                auto signature = entityManager->GetSignature(sceneNode.entity);
                signature.set(componentManager->GetComponentType<ScriptableClassComponent>(), true);
                entityManager->SetSignature(sceneNode.entity, signature);
            }
        }

        for (nlohmann::json nodeChildJson : nodeChildrenJsonArray) {
            nodeChildJson["parent_entity_id"] = sceneNode.entity;
            SceneNode childNode = ParseSceneJson(nodeChildJson, false);
            sceneNode.children.emplace_back(childNode);
        }

        return sceneNode;
    }
  public:
    SceneManager(SceneContext *vSceneContext, EntityManager *vEntityManager, ComponentManager *vComponentManager, AssetManager *vAssetManager) :
        sceneContext(vSceneContext), entityManager(vEntityManager), componentManager(vComponentManager), assetManager(vAssetManager) {
        timerManager = TimerManager::GetInstance();
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

//    void ChangeToScene(Entity entity) {
//        SceneNode rootSceneNode = SceneNode{.entity = entity};
//        Scene scene = Scene{.rootNode = rootSceneNode};
//        ChangeToScene(scene);
//    }

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
        SceneNode rootNode = ParseSceneJson(sceneJson, true);
        Scene loadedScene = Scene{.rootNode = rootNode};
        ChangeToScene(loadedScene);
        return loadedScene;
    }
};

#endif //SCENE_H
