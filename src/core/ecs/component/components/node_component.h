#ifndef NODE_COMPONENT_H
#define NODE_COMPONENT_H

#include <string>
#include <vector>

#include "../component.h"

using NodeType = std::uint32_t;

enum _NodeType {
    NodeType_INVALID = 0,
    NodeType_NODE = 1,
    NodeType_NODE2D = 2,
    NodeType_TEXT_LABEL = 3,
};

struct NodeComponent {
    NodeType type;
    std::string name;
    std::vector<std::string> tags;
};

#endif //NODE_COMPONENT_H
