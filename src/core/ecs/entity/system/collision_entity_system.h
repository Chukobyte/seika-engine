#ifndef COLLISION_ENTITY_SYSTEM_H
#define COLLISION_ENTITY_SYSTEM_H

#include "entity_system.h"
#include "../../../physics/collision/collision_context.h"
#include "../../component/components/collider_component.h"

class CollisionEntitySystem : public EntitySystem {
  private:
    std::map<Entity, CollisionResult> collisionResultsMap;
    CollisionContext *collisionContext = nullptr;
    ComponentManager *componentManager = nullptr;
  public:
    CollisionEntitySystem() {
        collisionContext = GD::GetContainer()->collisionContext;
        componentManager = GD::GetContainer()->componentManager;
        enabled = true;
    }

    void Initialize() override {}

    void Enable() override {}

    void Disable() override {}

    void UnregisterEntity(Entity entity) override {}

    void ProcessCollisions() {
        collisionResultsMap.clear();
        // TODO: Come up with a better more efficient solution
        for (Entity sourceEntity : entities) {
            std::vector<Entity> collidedEntities;
            for (Entity targetEntity : entities) {
                if (sourceEntity != targetEntity) {
                    if (CollisionResolver::DoesRectanglesCollide(Rect2(), Rect2())) {
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

    void Render() {}
};

#endif //COLLISION_ENTITY_SYSTEM_H
