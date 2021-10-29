#ifndef COLLISION_ENTITY_SYSTEM_H
#define COLLISION_ENTITY_SYSTEM_H

#include "entity_system.h"
#include "../../../physics/collision/collision_context.h"
#include "../../component/components/collider_component.h"
#include "../../../math/space_handler.h"

class CollisionEntitySystem : public EntitySystem {
  private:
    CollisionContext *collisionContext = nullptr;
    ComponentManager *componentManager = nullptr;
    CameraManager *cameraManager = nullptr;
    SceneManager *sceneManager = nullptr;
    Renderer2D *renderer = nullptr;
    RenderContext *renderContext = nullptr;
    Texture *colliderTexture = nullptr;
    Rect2 colliderDrawSource = Rect2(0.0f, 0.0f, 4.0f, 4.0f);

    Rect2 GetCollisionRectangle(Entity entity) {
        Transform2DComponent transform2DComponent = componentManager->GetComponent<Transform2DComponent>(entity);
        ColliderComponent colliderComponent = componentManager->GetComponent<ColliderComponent>(entity);
        Transform2DComponent parentTransform = SceneNodeHelper::GetCombinedParentsTransforms(sceneManager, componentManager, entity);
        return Rect2(transform2DComponent.position.x + parentTransform.position.x + colliderComponent.collider.x,
                     transform2DComponent.position.y + parentTransform.position.y + colliderComponent.collider.y,
                     transform2DComponent.scale.x * parentTransform.scale.x * colliderComponent.collider.w,
                     transform2DComponent.scale.y * parentTransform.scale.y * colliderComponent.collider.h);
    }

    // TODO: Finish implementing (or place logic elsewhere)
    Rect2 GetScreenCollisionRectangle(Entity entity) {
        Transform2DComponent transform2DComponent = componentManager->GetComponent<Transform2DComponent>(entity);
        ColliderComponent colliderComponent = componentManager->GetComponent<ColliderComponent>(entity);
        Transform2DComponent parentTransform = SceneNodeHelper::GetCombinedParentsTransforms(sceneManager, componentManager, entity);
        Camera2D camera = cameraManager->GetCurrentCamera2D();
        Vector2 collisionPosition = Vector2(transform2DComponent.position.x + parentTransform.position.x + colliderComponent.collider.x - camera.viewport.x,
                                            transform2DComponent.position.y + parentTransform.position.y + colliderComponent.collider.y - camera.viewport.y);
        return Rect2(collisionPosition,
                     transform2DComponent.scale.x * parentTransform.scale.x * colliderComponent.collider.w * camera.zoom.x,
                     transform2DComponent.scale.y * parentTransform.scale.y * colliderComponent.collider.h * camera.zoom.y);
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
        renderer = GD::GetContainer()->renderer;
        renderContext = GD::GetContainer()->renderContext;
        enabled = true;
    }

    void Initialize() override {
        colliderTexture = GD::GetContainer()->assetManager->GetTexture(DEFAULT_COLLIDER_ASSET_ID);
    }

    void Enable() override {}

    void Disable() override {}

    void UnregisterEntity(Entity entity) override {}

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
            Rect2 targetCollisionRectangle = GetCollisionRectangle(targetEntity);
//            Rect2 targetCollisionRectangle = GetScreenCollisionRectangle(targetEntity); // TODO: uncomment when function is finished
            if (CollisionResolver::DoesRectanglesCollide(mouseRectangle, targetCollisionRectangle)) {
                entitiesOnMouse.emplace_back(targetEntity);
            }
        }
        return entitiesOnMouse;
    }

    bool IsEntityOnMouse(const Entity entity, const Vector2 &mousePosition) {
        Rect2 entityCollisionRectangle = GetCollisionRectangle(entity);
//        Rect2 entityCollisionRectangle = GetScreenCollisionRectangle(entity); // TODO: uncomment when function is finished
        Rect2 mouseRectangle = Rect2(mousePosition, Vector2(1.0f, 1.0f));
//        std::cout << "entity rect2 = " << entityCollisionRectangle << std::endl;
//        std::cout << "mouse rect2 = " << mouseRectangle << std::endl;
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
