#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "../ecs/entity/entity.h"

struct SceneNode {
    Entity entity = NULL_ENTITY;
    Entity parent = NULL_ENTITY;
    std::vector<SceneNode> children;
};

struct Scene {
    SceneNode rootNode;
};

#endif //SCENE_H
