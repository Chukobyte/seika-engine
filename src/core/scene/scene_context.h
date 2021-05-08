#ifndef SCENE_CONTEXT_H
#define SCENE_CONTEXT_H

#include "../ecs/entity/entity.h"

class SceneContext {
  public:
    Entity currentSceneEntity;

    SceneContext() = default;
};

#endif //SCENE_CONTEXT_H
