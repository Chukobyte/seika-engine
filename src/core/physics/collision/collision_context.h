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
  private:
    static constexpr float FLOAT_EPSILON = 0.001f;

    static bool IsFloatGreaterOrEqual(float a, float b) {
        return fabs(a - b) < FLOAT_EPSILON || a > b;
    }
  public:
    static bool DoesRectanglesCollide(Rect2 sourceRect, Rect2 targetRect) {
        return IsFloatGreaterOrEqual(sourceRect.x + sourceRect.w, targetRect.x) &&
               IsFloatGreaterOrEqual(targetRect.x + targetRect.w, sourceRect.x) &&
               IsFloatGreaterOrEqual(sourceRect.y + sourceRect.h, targetRect.y) &&
               IsFloatGreaterOrEqual(targetRect.y + targetRect.h, sourceRect.y);
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

    bool HasEntityCollided(Entity entity) {
        return collisionResultsMap.count(entity) > 0;
    }

    std::vector<Entity> GetEntitiesCollidedWith(Entity entity) {
        if (HasEntityCollided(entity)) {
            return collisionResultsMap[entity].collidedEntities;
        }
        std::vector<Entity> entitiesColliderWith;
        return entitiesColliderWith;
    }
};

#endif //COLLISION_CONTEXT_H
