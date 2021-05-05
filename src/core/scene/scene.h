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
#include "../ecs/component/components/scriptable_class_component.h"

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
    EntityManager *entityManager = nullptr;
    ComponentManager *componentManager = nullptr;
    AssetManager *assetManager = nullptr;

    SceneNode ParseSceneJson(nlohmann::json nodeJson) {
        SceneNode sceneNode = SceneNode{.entity = entityManager->CreateEntity()};
        std::string nodeName = nodeJson["name"].get<std::string>();
        std::string nodeType = nodeJson["type"].get<std::string>();
        nlohmann::json nodeTagsJsonArray = nodeJson["tags"].get<nlohmann::json>();
        std::string nodeExternalSceneSource = nodeJson["external_scene_source"].get<std::string>();
        nlohmann::json nodeComponentJsonArray = nodeJson["components"].get<nlohmann::json>();
        nlohmann::json nodeChildrenJsonArray = nodeJson["children"].get<nlohmann::json>();

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
            } else if (nodeComponentType == "sprite") {
                std::string nodeTexturePath = nodeComponentObjectJson["texture_path"].get<std::string>();
                nlohmann::json nodeDrawSourceJson = nodeComponentObjectJson["draw_source"].get<nlohmann::json>();
                float nodeDrawSourceX = nodeDrawSourceJson["x"].get<float>();
                float nodeDrawSourceY = nodeDrawSourceJson["y"].get<float>();
                float nodeDrawSourceWidth = nodeDrawSourceJson["width"].get<float>();
                float nodeDrawSourceHeight = nodeDrawSourceJson["height"].get<float>();

                componentManager->AddComponent(sceneNode.entity, SpriteComponent{
                    .texture = assetManager->GetTexture(nodeTexturePath),
                    .drawSource = Rect2(nodeDrawSourceX, nodeDrawSourceY, nodeDrawSourceWidth, nodeDrawSourceHeight)
                });
                auto signature = entityManager->GetSignature(sceneNode.entity);
                signature.set(componentManager->GetComponentType<SpriteComponent>(), true);
                entityManager->SetSignature(sceneNode.entity, signature);
            } else if (nodeComponentType == "animated_sprite") {
                std::string nodeCurrentAnimationName = nodeComponentObjectJson["current_animation"].get<std::string>();
                bool nodeIsPlaying = nodeComponentObjectJson["is_playing"].get<bool>();
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
                    .isPlaying = nodeIsPlaying
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
            SceneNode childNode = ParseSceneJson(nodeChildJson);
            sceneNode.children.emplace_back(childNode);
        }

        return sceneNode;
    }
  public:
    SceneManager(EntityManager *vEntityManager, ComponentManager *vComponentManager, AssetManager *vAssetManager) :
        entityManager(vEntityManager), componentManager(vComponentManager), assetManager(vAssetManager) {
    }

    void AddSingletonScene(Entity singletonEntity) {
        SceneNode sceneNode = SceneNode{.entity = singletonEntity};
        Scene scene = Scene{.rootNode = sceneNode};
        entityToMainScenesMap.emplace(singletonEntity, scene);
    }

    void ChangeToScene(Entity entity) {
        SceneNode rootSceneNode = SceneNode{.entity = entity};
        Scene scene = Scene{.rootNode = rootSceneNode};
        ChangeToScene(scene);
    }

    void ChangeToScene(Scene scene) {
        if (currentScene.rootNode.entity != NO_ENTITY) {
            RemoveNode(currentScene.rootNode.entity);
        }
        currentScene = scene;
        entityToMainScenesMap.emplace(currentScene.rootNode.entity, currentScene);
        AddChild(NO_ENTITY, currentScene.rootNode.entity);
    }

    void AddChild(Entity parent, Entity child) {
        if (parent != NO_ENTITY) {
            assert((entityToSceneNodeMap.count(parent) > 0) && "Parent scene node doesn't exist!");
            SceneNode parentNode = entityToSceneNodeMap[parent];
            parentNode.children.emplace_back(SceneNode{.entity = child});
            entityToSceneNodeMap[parent] = parentNode;
        }
        SceneNode childNode = SceneNode{.entity = child, .parent = parent};
        entityToSceneNodeMap.emplace(childNode.entity, childNode);
    }

    Entity GetParent(Entity entity) {
        if (IsEntityInScene(entity)) {
            SceneNode sceneNode = entityToSceneNodeMap[entity];
            return sceneNode.parent;
        }
        return NO_ENTITY;
    }

    void RemoveNode(Entity entity) {
        SceneNode node = entityToSceneNodeMap[entity];
        entityToSceneNodeMap.erase(entity);
        entityToMainScenesMap.erase(entity);
        entitiesRecentlyRemoved.emplace_back(entity);
        for (SceneNode childNode : node.children) {
            RemoveNode(childNode.entity);
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
        SceneNode rootNode = ParseSceneJson(sceneJson);
        Scene loadedScene = Scene{.rootNode = rootNode};
        ChangeToScene(loadedScene);
        return loadedScene;
    }
};

#endif //SCENE_H
