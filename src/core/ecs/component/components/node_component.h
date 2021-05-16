#ifndef NODE_COMPONENT_H
#define NODE_COMPONENT_H

#include <string>
#include <vector>

#include "../component.h"

using NodeType = std::uint32_t;

enum _NodeType {
    NodeType_INVALID = 0,
    NodeType_NODE = 2,
    NodeType_NODE2D = 4,
    NodeType_SPRITE = 8,
    NodeType_ANIMATED_SPRITE = 16,
    NodeType_TEXT_LABEL = 32,
    NodeType_COLLISION_SHAPE2D = 64,
};

enum _NodeTypeInheritance {
    NodeTypeInheritance_NODE = NodeType_NODE,
    NodeTypeInheritance_NODE2D = NodeType_NODE | NodeType_NODE2D,
    NodeTypeInheritance_SPRITE = NodeType_NODE | NodeType_NODE2D | NodeType_SPRITE,
    NodeTypeInheritance_ANIMATED_SPRITE = NodeType_NODE | NodeType_NODE2D | NodeType_ANIMATED_SPRITE,
    NodeTypeInheritance_TEXT_LABEL = NodeType_NODE | NodeType_NODE2D | NodeType_TEXT_LABEL,
    NodeTypeInheritance_COLLISION_SHAPE2D = NodeType_NODE | NodeType_NODE2D | NodeType_COLLISION_SHAPE2D,
};

struct NodeComponent {
    NodeType type;
    std::string name;
    std::vector<std::string> tags;
};

#endif //NODE_COMPONENT_H
