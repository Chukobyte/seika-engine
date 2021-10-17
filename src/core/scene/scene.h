#ifndef SCENE_H
#define SCENE_H

#include <vector>

struct SceneNode {
    Entity entity = NO_ENTITY;
    Entity parent = NO_ENTITY;
    std::vector<SceneNode> children;
};

struct Scene {
    SceneNode rootNode;
};

#endif //SCENE_H
