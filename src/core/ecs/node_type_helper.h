#ifndef NODE_TYPE_HELPER_H
#define NODE_TYPE_HELPER_H

#include "component/components/node_component.h"

#include <map>

class NodeTypeHelper {
  private:
    static const std::string NODE_TYPE_INVALID;
    static const std::string NODE_TYPE_NODE;
    static const std::string NODE_TYPE_NODE2D;
    static const std::string NODE_TYPE_SPRITE;
    static const std::string NODE_TYPE_ANIMATED_SPRITE;
    static const std::string NODE_TYPE_TEXT_LABEL;
    static const std::string NODE_TYPE_COLLISION_SHAPE2D;

    static std::map<NodeType, std::string> NODE_TYPE_TO_STRING_MAP;
    static std::map<std::string, NodeType> NODE_STRING_TO_TYPE_MAP;
    static std::map<NodeType, NodeTypeInheritance> NODE_TYPE_TO_INHERITANCE_MAP;
  public:
    static std::string GetNodeTypeString(NodeType nodeType) {
        if (NODE_TYPE_TO_STRING_MAP.count(nodeType) > 0) {
            return NODE_TYPE_TO_STRING_MAP[nodeType];
        }
        return NODE_TYPE_INVALID;
    }
    static NodeType GetNodeTypeInt(const std::string &nodeTypeString) {
        if (NODE_STRING_TO_TYPE_MAP.count(nodeTypeString) > 0) {
            return NODE_STRING_TO_TYPE_MAP[nodeTypeString];
        }
        return NodeType_INVALID;
    }

    static NodeTypeInheritance GetNodeTypeInheritanceInt(NodeType nodeType) {
        if (NODE_TYPE_TO_INHERITANCE_MAP.count(nodeType) > 0) {
            return NODE_TYPE_TO_INHERITANCE_MAP[nodeType];
        }
        return NodeTypeInheritance_INVALID;
    }

    static bool IsNameDefaultNodeClass(const std::string &className) {
        if (GetNodeTypeInt(className) != NodeType_INVALID) {
            return true;
        }
        return false;
    }
};

#endif //NODE_TYPE_HELPER_H
