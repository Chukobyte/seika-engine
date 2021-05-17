#include "node_type_helper.h"

const std::string NodeTypeHelper::NODE_TYPE_INVALID = "Invalid";
const std::string NodeTypeHelper::NODE_TYPE_NODE = "Node";
const std::string NodeTypeHelper::NODE_TYPE_NODE2D = "Node2D";
const std::string NodeTypeHelper::NODE_TYPE_SPRITE = "Sprite";
const std::string NodeTypeHelper::NODE_TYPE_ANIMATED_SPRITE = "AnimatedSprite";
const std::string NodeTypeHelper::NODE_TYPE_TEXT_LABEL = "TextLabel";
const std::string NodeTypeHelper::NODE_TYPE_COLLISION_SHAPE2D = "CollisionShape2D";

std::map<NodeType, std::string> NodeTypeHelper::NODE_TYPE_TO_STRING_MAP = {
    {NodeType_NODE, NODE_TYPE_NODE},
    {NodeType_NODE2D, NODE_TYPE_NODE2D},
    {NodeType_SPRITE, NODE_TYPE_SPRITE},
    {NodeType_ANIMATED_SPRITE, NODE_TYPE_ANIMATED_SPRITE},
    {NodeType_TEXT_LABEL, NODE_TYPE_TEXT_LABEL},
    {NodeType_COLLISION_SHAPE2D, NODE_TYPE_COLLISION_SHAPE2D},
};

std::map<std::string, NodeType> NodeTypeHelper::NODE_STRING_TO_TYPE_MAP = {
    {NODE_TYPE_NODE, NodeType_NODE},
    {NODE_TYPE_NODE2D, NodeType_NODE2D},
    {NODE_TYPE_SPRITE, NodeType_SPRITE},
    {NODE_TYPE_ANIMATED_SPRITE, NodeType_ANIMATED_SPRITE},
    {NODE_TYPE_TEXT_LABEL, NodeType_TEXT_LABEL},
    {NODE_TYPE_COLLISION_SHAPE2D, NodeType_COLLISION_SHAPE2D},
};

std::map<NodeType, NodeTypeInheritance> NodeTypeHelper::NODE_TYPE_TO_INHERITANCE_MAP = {
    {NodeType_NODE, NodeTypeInheritance_NODE},
    {NodeType_NODE2D, NodeTypeInheritance_NODE2D},
    {NodeType_SPRITE, NodeTypeInheritance_SPRITE},
    {NodeType_ANIMATED_SPRITE, NodeTypeInheritance_ANIMATED_SPRITE},
    {NodeType_TEXT_LABEL, NodeTypeInheritance_TEXT_LABEL},
    {NodeType_COLLISION_SHAPE2D, NodeTypeInheritance_COLLISION_SHAPE2D},
};
