#ifndef NODE_TYPE_HELPER_H
#define NODE_TYPE_HELPER_H

#include "component/components/node_component.h"

class NodeTypeHelper {
  private:
    static const std::string NODE_TYPE_INVALID;
    static const std::string NODE_TYPE_NODE;
    static const std::string NODE_TYPE_NODE2D;
    static const std::string NODE_TYPE_TEXT_LABEL;
  public:
    static std::string GetNodeTypeString(NodeType nodeType) {
        switch (nodeType) {
        case NodeType_NODE:
            return NODE_TYPE_NODE;
        case NodeType_NODE2D:
            return NODE_TYPE_NODE2D;
        case NodeType_TEXT_LABEL:
            return NODE_TYPE_TEXT_LABEL;
        default:
            return NODE_TYPE_INVALID;
        }
    }
    static NodeType GetNodeTypeInt(const std::string &nodeTypeString) {
        if (nodeTypeString == NODE_TYPE_NODE) {
            return  NodeType_NODE;
        } else if(nodeTypeString == NODE_TYPE_NODE2D) {
            return NodeType_NODE2D;
        } else if(nodeTypeString == NODE_TYPE_TEXT_LABEL) {
            return NodeType_TEXT_LABEL;
        }
        return NodeType_INVALID;
    }
};

#endif //NODE_TYPE_HELPER_H
