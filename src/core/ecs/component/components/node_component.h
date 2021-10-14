#ifndef NODE_COMPONENT_H
#define NODE_COMPONENT_H

#include <string>
#include <vector>

#include "../component.h"

using NodeType = std::uint32_t;
using NodeTypeInheritance = std::uint32_t;

enum _NodeType {
    NodeType_INVALID = 0,
    NodeType_NODE = 2,
    // 2D
    NodeType_NODE2D = 4,
    NodeType_SPRITE = 8,
    NodeType_ANIMATED_SPRITE = 16,
    NodeType_TEXT_LABEL = 32,
    NodeType_COLLISION_SHAPE2D = 64,
    // 3D
    NodeType_SPATIAL = 128,
    NodeType_TEXTURE_CUBE = 256,
    NodeType_DIRECTIONAL_LIGHT = 512,
    NodeType_POINT_LIGHT = 1024,
    NodeType_SPOT_LIGHT = 2048,
};

enum _NodeTypeInheritance {
    NodeTypeInheritance_INVALID = NodeType_INVALID,
    NodeTypeInheritance_NODE = NodeType_NODE,
    // 2D
    NodeTypeInheritance_NODE2D = NodeType_NODE | NodeType_NODE2D,
    NodeTypeInheritance_SPRITE = NodeType_NODE | NodeType_NODE2D | NodeType_SPRITE,
    NodeTypeInheritance_ANIMATED_SPRITE = NodeType_NODE | NodeType_NODE2D | NodeType_ANIMATED_SPRITE,
    NodeTypeInheritance_TEXT_LABEL = NodeType_NODE | NodeType_NODE2D | NodeType_TEXT_LABEL,
    NodeTypeInheritance_COLLISION_SHAPE2D = NodeType_NODE | NodeType_NODE2D | NodeType_COLLISION_SHAPE2D,
    // 3D
    NodeTypeInheritance_SPATIAL = NodeType_NODE | NodeType_SPATIAL,
    NodeTypeInheritance_TEXTURE_CUBE = NodeType_NODE | NodeType_SPATIAL | NodeType_TEXTURE_CUBE,
    NodeTypeInheritance_DIRECTIONAL_LIGHT = NodeType_NODE | NodeType_SPATIAL | NodeType_DIRECTIONAL_LIGHT,
    NodeTypeInheritance_POINT_LIGHT = NodeType_NODE | NodeType_SPATIAL | NodeType_POINT_LIGHT,
    NodeTypeInheritance_SPOT_LIGHT = NodeType_NODE | NodeType_SPATIAL | NodeType_SPOT_LIGHT,
};

struct NodeComponent {
    NodeType type;
    std::string name;
    std::vector<std::string> tags;
    bool visible = true;
};

#endif //NODE_COMPONENT_H
