#ifndef COLLISION_CONTEXT_H
#define COLLISION_CONTEXT_H

#include <vector>
#include <map>

#include "../../ecs/entity/entity.h"
#include "../../math/rect2.h"

struct CollisionResult {
    Entity sourceEntity;
    std::vector<Entity> collidedEntities;
};

class CollisionResolver {
  public:
    static bool DoesRectanglesCollide(Rect2 sourceRect, Rect2 targetRect) {
        return sourceRect.x + sourceRect.w >= targetRect.x &&
               targetRect.x + targetRect.w >= sourceRect.x &&
               sourceRect.y + sourceRect.h >= targetRect.y &&
               targetRect.y + targetRect.h >= sourceRect.y;
    }
};

class CollisionContext {
  private:
    std::map<Entity, CollisionResult> collisionResultsMap;
  public:
    void ClearCollisionData() {
        collisionResultsMap.clear();
    }

    void RegisterCollisionResult(CollisionResult collisionResult) {
        collisionResultsMap.emplace(collisionResult.sourceEntity, collisionResult);
    }
};

#endif //COLLISION_CONTEXT_H
