#ifndef COLLISION_ENTITY_SYSTEM_H
#define COLLISION_ENTITY_SYSTEM_H

#include "entity_system.h"
#include "../../physics/collision/collision_context.h"
#include "../component/components/collider_component.h"
#include "../../math/space_handler.h"

class CollisionEntitySystem : public EntitySystem {
  private:
    CollisionContext *collisionContext = nullptr;
    ComponentManager *componentManager = nullptr;
    CameraManager *cameraManager = nullptr;
    SceneManager *sceneManager = nullptr;
    Renderer2D *renderer = nullptr;
    RenderContext *renderContext = nullptr;
    Texture *colliderTexture = nullptr;
    Rect2 colliderDrawSource = Rect2(0.0f, 0.0f, 1.0f, 1.0f);

    Rect2 GetCollisionRectangle(Entity entity) {
        Transform2DComponent transform2DComponent = componentManager->GetComponent<Transform2DComponent>(entity);
        ColliderComponent colliderComponent = componentManager->GetComponent<ColliderComponent>(entity);
        Transform2DComponent parentTransform = SceneNodeHelper::GetCombinedParentsTransforms(sceneManager, componentManager, entity);
        return Rect2(transform2DComponent.position.x + parentTransform.position.x + colliderComponent.collider.x,
                     transform2DComponent.position.y + parentTransform.position.y + colliderComponent.collider.y,
                     transform2DComponent.scale.x * parentTransform.scale.x * colliderComponent.collider.w,
                     transform2DComponent.scale.y * parentTransform.scale.y * colliderComponent.collider.h);
    }

    Rect2 GetScreenCollisionRectangle(Entity entity) {
        Transform2DComponent transform2DComponent = componentManager->GetComponent<Transform2DComponent>(entity);
        ColliderComponent colliderComponent = componentManager->GetComponent<ColliderComponent>(entity);
        Transform2DComponent parentTransform = SceneNodeHelper::GetCombinedParentsTransforms(sceneManager, componentManager, entity);
        Vector2 collisionPosition = Vector2(transform2DComponent.position.x + parentTransform.position.x + colliderComponent.collider.x,
                                            transform2DComponent.position.y + parentTransform.position.y + colliderComponent.collider.y);

        glm::vec4 clipSpace = renderer->GetProjection() *
                              glm::vec4(collisionPosition.x, collisionPosition.y, 0.0f, 1.0f);

        if (clipSpace.w < 0.1f) {
            return Rect2(Vector2(-10.0f, -10.0f), Vector2(1.0f, 1.0f));
        }

        glm::vec3 ndcSpace = glm::vec3(clipSpace.x / clipSpace.w, clipSpace.y / clipSpace.w, clipSpace.z / clipSpace.w);
        const float windowWidth = GD::GetContainer()->renderContext->currentWindowWidth;
        const float windowHeight = GD::GetContainer()->renderContext->currentWindowHeight;
        Vector2 collisionScreenPosition = Vector2();
        collisionScreenPosition.x = (windowWidth / 2 * ndcSpace.x) + (ndcSpace.x + windowWidth / 2);
        collisionScreenPosition.y = -(windowHeight / 2 * ndcSpace.y) + (ndcSpace.y + windowHeight / 2);

        Camera2D camera = cameraManager->GetCurrentCamera2D();
        Vector2 collisionScreenScale = Vector2(transform2DComponent.scale.x * parentTransform.scale.x * colliderComponent.collider.w * camera.zoom.x,
                                               transform2DComponent.scale.y * parentTransform.scale.y * colliderComponent.collider.h * camera.zoom.y);
        ProjectProperties *projectProperties = ProjectProperties::GetInstance();
        collisionScreenScale.x *= windowWidth / static_cast<float>(projectProperties->windowWidth);
        collisionScreenScale.y *= windowHeight / static_cast<float>(projectProperties->windowHeight);
        return Rect2(collisionScreenPosition, collisionScreenScale);
    }

    bool IsTargetCollisionEntityInExceptionList(Entity sourceEntity, Entity targetEntity) {
        ColliderComponent sourceColliderComponent = componentManager->GetComponent<ColliderComponent>(sourceEntity);
        return std::find(sourceColliderComponent.collisionExceptions.begin(), sourceColliderComponent.collisionExceptions.end(), targetEntity) != sourceColliderComponent.collisionExceptions.end();
    }
  public:
    CollisionEntitySystem() {
        collisionContext = GD::GetContainer()->collisionContext;
        componentManager = GD::GetContainer()->componentManager;
        cameraManager = GD::GetContainer()->cameraManager;
        sceneManager = GD::GetContainer()->sceneManager;
        renderer = GD::GetContainer()->renderer2D;
        renderContext = GD::GetContainer()->renderContext;
        enabled = true;
    }

    void Initialize() override {
        colliderTexture = GD::GetContainer()->assetManager->GetTexture(BLANK_WHITE_TEXTURE_ASSET_ID);
    }

    void Enable() override {}

    void Disable() override {}

    void OnEntityDestroyed(Entity entity) override {}

//    void ProcessCollisions() {
//        collisionContext->ClearCollisionData();
//        // TODO: Come up with a better more efficient solution
//        for (Entity sourceEntity : entities) {
//            std::vector<Entity> collidedEntities;
//            for (Entity targetEntity : entities) {
//                if (!IsTargetCollisionEntityInExceptionList(sourceEntity, targetEntity)) {
//                    Rect2 sourceCollisionRectangle = GetCollisionRectangle(sourceEntity);
//                    Rect2 targetCollisionRectangle = GetCollisionRectangle(targetEntity);
//                    if (CollisionResolver::DoesRectanglesCollide(sourceCollisionRectangle, targetCollisionRectangle)) {
//                        collidedEntities.emplace_back(targetEntity);
//                        // TODO: emit signal if Area2D like functionality for entering and exiting is required
//                    }
//                }
//            }
//            if (collidedEntities.size() > 0) {
//                collisionContext->RegisterCollisionResult(
//                CollisionResult{
//                    .sourceEntity = sourceEntity,
//                    .collidedEntities = collidedEntities
//                });
//            }
//        }
//    }

    void ProcessEntityCollisions(Entity sourceEntity) {
        collisionContext->ClearCollisionData();
        std::vector<Entity> collidedEntities;
        for (Entity targetEntity : entities) {
            if (!IsTargetCollisionEntityInExceptionList(sourceEntity, targetEntity)) {
                Rect2 sourceCollisionRectangle = GetCollisionRectangle(sourceEntity);
                Rect2 targetCollisionRectangle = GetCollisionRectangle(targetEntity);
                if (CollisionResolver::DoesRectanglesCollide(sourceCollisionRectangle, targetCollisionRectangle)) {
                    collidedEntities.emplace_back(targetEntity);
                    // TODO: emit signal if Area2D like functionality for entering and exiting is required
                }
            }
        }
        if (collidedEntities.size() > 0) {
            collisionContext->RegisterCollisionResult(
            CollisionResult{
                .sourceEntity = sourceEntity,
                .collidedEntities = collidedEntities
            });
        }
    }

    std::vector<Entity> GetEntitiesOnMouse(const Vector2 mousePosition) {
        std::vector<Entity> entitiesOnMouse;
        Rect2 mouseRectangle = Rect2(mousePosition, Vector2(1.0f, 1.0f));
        for (Entity targetEntity : entities) {
            Rect2 targetCollisionRectangle = GetScreenCollisionRectangle(targetEntity);
            if (CollisionResolver::DoesRectanglesCollide(mouseRectangle, targetCollisionRectangle)) {
                entitiesOnMouse.emplace_back(targetEntity);
            }
        }
        return entitiesOnMouse;
    }

    bool IsEntityOnMouse(const Entity entity, const Vector2 &mousePosition) {
        Rect2 entityCollisionRectangle = GetScreenCollisionRectangle(entity);
        Rect2 mouseRectangle = Rect2(mousePosition, Vector2(1.0f, 1.0f));
        if (CollisionResolver::DoesRectanglesCollide(entityCollisionRectangle, mouseRectangle)) {
            return true;
        }
        return false;
    }

    void Render() {
        for (Entity entity : entities) {
            Transform2DComponent transform2DComponent = componentManager->GetComponent<Transform2DComponent>(entity);
            ColliderComponent colliderComponent = componentManager->GetComponent<ColliderComponent>(entity);
            Transform2DComponent parentTransform = SceneNodeHelper::GetCombinedParentsTransforms(sceneManager, componentManager, entity);
            Vector2 parentPosition = parentTransform.position;
            Vector2 colliderPosition = Vector2(colliderComponent.collider.x, colliderComponent.collider.y);
            Vector2 drawDestinationPosition = SpaceHandler::WorldToScreen(transform2DComponent.position + parentPosition + colliderPosition,
                                              transform2DComponent.ignoreCamera);
            Rect2 colliderDrawDestination = Rect2(drawDestinationPosition,
                                                  Vector2(transform2DComponent.scale.x * parentTransform.scale.x * colliderComponent.collider.w,
                                                          transform2DComponent.scale.y * parentTransform.scale.y * colliderComponent.collider.h));
            if (!transform2DComponent.ignoreCamera) {
                Camera2D camera = cameraManager->GetCurrentCamera2D();
                colliderDrawDestination.w *= camera.zoom.x;
                colliderDrawDestination.h *= camera.zoom.y;
            }
            renderer->BatchDrawSprite(
                colliderTexture,
                colliderDrawSource,
                colliderDrawDestination,
                transform2DComponent.zIndex + parentTransform.zIndex,
                transform2DComponent.rotation,
                colliderComponent.color
            );
        }
    }
};

#endif //COLLISION_ENTITY_SYSTEM_H
