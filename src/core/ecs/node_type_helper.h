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
        switch (nodeType) {
        case NodeType_NODE:
            return NODE_TYPE_NODE;
        case NodeType_NODE2D:
            return NODE_TYPE_NODE2D;
        case NodeType_SPRITE:
            return NODE_TYPE_SPRITE;
        case NodeType_ANIMATED_SPRITE:
            return NODE_TYPE_ANIMATED_SPRITE;
        case NodeType_TEXT_LABEL:
            return NODE_TYPE_TEXT_LABEL;
        case NodeType_COLLISION_SHAPE2D:
            return NODE_TYPE_COLLISION_SHAPE2D;
        default:
            return NODE_TYPE_INVALID;
        }
    }
    static NodeType GetNodeTypeInt(const std::string &nodeTypeString) {
        if (nodeTypeString == NODE_TYPE_NODE) {
            return  NodeType_NODE;
        } else if(nodeTypeString == NODE_TYPE_NODE2D) {
            return NodeType_NODE2D;
        } else if(nodeTypeString == NODE_TYPE_SPRITE) {
            return NodeType_SPRITE;
        } else if(nodeTypeString == NODE_TYPE_ANIMATED_SPRITE) {
            return NodeType_ANIMATED_SPRITE;
        } else if(nodeTypeString == NODE_TYPE_TEXT_LABEL) {
            return NodeType_TEXT_LABEL;
        } else if(nodeTypeString == NODE_TYPE_COLLISION_SHAPE2D) {
            return NodeType_COLLISION_SHAPE2D;
        }

        return NodeType_INVALID;
    }

    static NodeTypeInheritance GetNodeTypeInheritanceInt(NodeType nodeType) {
        if (NODE_TYPE_TO_INHERITANCE_MAP.count(nodeType) > 0) {
            return NODE_TYPE_TO_INHERITANCE_MAP[nodeType];
        }
        return NodeTypeInheritance_INVALID;
    }
};

#endif //NODE_TYPE_HELPER_H
