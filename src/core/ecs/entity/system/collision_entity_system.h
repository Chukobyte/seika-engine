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
    Renderer *renderer = nullptr;
    Texture2D *colliderTexture = nullptr;
    Rect2 colliderDrawSource = Rect2(0.0f, 0.0f, 4.0f, 4.0f);

    Vector2 GetParentPosition(Entity entity) {
        Entity parentEntity = sceneManager->GetParent(entity);
        if (parentEntity == NO_ENTITY) {
            return {0, 0};
        } else {
            Transform2DComponent transform2DComponent = componentManager->GetComponent<Transform2DComponent>(parentEntity);
            return transform2DComponent.position;
        }
    }

    Rect2 GetCollisionRectangle(Entity entity) {
        Transform2DComponent transform2DComponent = componentManager->GetComponent<Transform2DComponent>(entity);
        ColliderComponent colliderComponent = componentManager->GetComponent<ColliderComponent>(entity);
        Vector2 parentPosition = GetParentPosition(entity);
        return Rect2(transform2DComponent.position.x + parentPosition.x + (colliderComponent.collider.x * transform2DComponent.scale.x),
                     transform2DComponent.position.y + parentPosition.y + (colliderComponent.collider.y * transform2DComponent.scale.y),
                     transform2DComponent.scale.x + colliderComponent.collider.w,
                     transform2DComponent.scale.y + colliderComponent.collider.h);
    }
  public:
    CollisionEntitySystem() {
        collisionContext = GD::GetContainer()->collisionContext;
        componentManager = GD::GetContainer()->componentManager;
        cameraManager = GD::GetContainer()->cameraManager;
        sceneManager = GD::GetContainer()->sceneManager;
        renderer = GD::GetContainer()->renderer;
        enabled = true;
    }

    void Initialize() override {
        colliderTexture = GD::GetContainer()->assetManager->GetTexture(DEFAULT_COLLIDER_ASSET_ID);
    }

    void Enable() override {}

    void Disable() override {}

    void UnregisterEntity(Entity entity) override {}

    void ProcessCollisions() {
        collisionContext->ClearCollisionData();
        // TODO: Come up with a better more efficient solution
        for (Entity sourceEntity : entities) {
            std::vector<Entity> collidedEntities;
            for (Entity targetEntity : entities) {
                if (sourceEntity != targetEntity) {
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
    }

    void Render() {
        for (Entity entity : entities) {
            Transform2DComponent transform2DComponent = componentManager->GetComponent<Transform2DComponent>(entity);
            ColliderComponent colliderComponent = componentManager->GetComponent<ColliderComponent>(entity);
            Vector2 parentPosition = GetParentPosition(entity);
            Vector2 drawDestinationPosition = SpaceHandler::WorldToScreen(Vector2(
                                                  transform2DComponent.position.x + parentPosition.x + (colliderComponent.collider.x * transform2DComponent.scale.x),
                                                  transform2DComponent.position.y + parentPosition.y + (colliderComponent.collider.y * transform2DComponent.scale.y)),
                                              transform2DComponent.ignoreCamera);
            Rect2 colliderDrawDestination = Rect2(drawDestinationPosition,
                                                  Vector2(transform2DComponent.scale.x * colliderComponent.collider.w,
                                                          transform2DComponent.scale.y * colliderComponent.collider.h));
            if (!transform2DComponent.ignoreCamera) {
                Camera camera = cameraManager->GetCurrentCamera();
                colliderDrawDestination.w *= camera.zoom.x;
                colliderDrawDestination.h *= camera.zoom.y;
            }
            renderer->DrawSprite(colliderTexture, &colliderDrawSource, &colliderDrawDestination, transform2DComponent.zIndex);
        }
    }
};

#endif //COLLISION_ENTITY_SYSTEM_H
