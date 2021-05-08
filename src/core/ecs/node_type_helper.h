#ifndef NODE_TYPE_HELPER_H
#define NODE_TYPE_HELPER_H

#include "component/components/node_component.h"

class NodeTypeHelper {
  private:
    static const std::string NODE_TYPE_INVALID;
    static const std::string NODE_TYPE_NODE;
    static const std::string NODE_TYPE_NODE2D;
  public:
    static std::string GetNodeTypeString(NodeType nodeType) {
        switch (nodeType) {
        case NodeType_NODE:
            return NODE_TYPE_NODE;
        case NodeType_NODE2D:
            return NODE_TYPE_NODE2D;
        default:
            return NODE_TYPE_INVALID;
        }
    }
    static NodeType GetNodeTypeInt(const std::string &nodeTypeString) {
        if (nodeTypeString == NODE_TYPE_NODE) {
            return  NodeType_NODE;
        } else if(nodeTypeString == NODE_TYPE_NODE2D) {
            return NodeType_NODE2D;
        }
        return NodeType_INVALID;
    }
};

#endif //NODE_TYPE_HELPER_H
