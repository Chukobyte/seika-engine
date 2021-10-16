#include "node_type_helper.h"

const std::string NodeTypeHelper::NODE_TYPE_INVALID = "Invalid";
const std::string NodeTypeHelper::NODE_TYPE_NODE = "Node";
const std::string NodeTypeHelper::NODE_TYPE_TIMER = "Timer";
//2D
const std::string NodeTypeHelper::NODE_TYPE_NODE2D = "Node2D";
const std::string NodeTypeHelper::NODE_TYPE_SPRITE = "Sprite";
const std::string NodeTypeHelper::NODE_TYPE_ANIMATED_SPRITE = "AnimatedSprite";
const std::string NodeTypeHelper::NODE_TYPE_TEXT_LABEL = "TextLabel";
const std::string NodeTypeHelper::NODE_TYPE_COLLISION_SHAPE2D = "CollisionShape2D";
//3D
const std::string NodeTypeHelper::NODE_TYPE_SPATIAL = "Spatial";
const std::string NodeTypeHelper::NODE_TYPE_TEXTURE_CUBE = "TextureCube";
const std::string NodeTypeHelper::NODE_TYPE_DIRECTIONAL_LIGHT = "DirectionalLight";
const std::string NodeTypeHelper::NODE_TYPE_POINT_LIGHT = "PointLight";
const std::string NodeTypeHelper::NODE_TYPE_SPOT_LIGHT = "SpotLight";

std::map<NodeType, std::string> NodeTypeHelper::NODE_TYPE_TO_STRING_MAP = {
    {NodeType_NODE, NODE_TYPE_NODE},
    {NodeType_TIMER, NODE_TYPE_TIMER},
    {NodeType_NODE2D, NODE_TYPE_NODE2D},
    {NodeType_SPRITE, NODE_TYPE_SPRITE},
    {NodeType_ANIMATED_SPRITE, NODE_TYPE_ANIMATED_SPRITE},
    {NodeType_TEXT_LABEL, NODE_TYPE_TEXT_LABEL},
    {NodeType_COLLISION_SHAPE2D, NODE_TYPE_COLLISION_SHAPE2D},
    {NodeType_SPATIAL, NODE_TYPE_SPATIAL},
    {NodeType_TEXTURE_CUBE, NODE_TYPE_TEXTURE_CUBE},
    {NodeType_DIRECTIONAL_LIGHT, NODE_TYPE_DIRECTIONAL_LIGHT},
    {NodeType_POINT_LIGHT, NODE_TYPE_POINT_LIGHT},
    {NodeType_SPOT_LIGHT, NODE_TYPE_SPOT_LIGHT},
};

std::map<std::string, NodeType> NodeTypeHelper::NODE_STRING_TO_TYPE_MAP = {
    {NODE_TYPE_NODE, NodeType_NODE},
    {NODE_TYPE_TIMER, NodeType_TIMER},
    {NODE_TYPE_NODE2D, NodeType_NODE2D},
    {NODE_TYPE_SPRITE, NodeType_SPRITE},
    {NODE_TYPE_ANIMATED_SPRITE, NodeType_ANIMATED_SPRITE},
    {NODE_TYPE_TEXT_LABEL, NodeType_TEXT_LABEL},
    {NODE_TYPE_COLLISION_SHAPE2D, NodeType_COLLISION_SHAPE2D},
    {NODE_TYPE_SPATIAL, NodeType_SPATIAL},
    {NODE_TYPE_TEXTURE_CUBE, NodeType_TEXTURE_CUBE},
    {NODE_TYPE_DIRECTIONAL_LIGHT, NodeType_DIRECTIONAL_LIGHT},
    {NODE_TYPE_POINT_LIGHT, NodeType_POINT_LIGHT},
    {NODE_TYPE_SPOT_LIGHT, NodeType_SPOT_LIGHT},
};

std::map<NodeType, NodeTypeInheritance> NodeTypeHelper::NODE_TYPE_TO_INHERITANCE_MAP = {
    {NodeType_NODE, NodeTypeInheritance_NODE},
    {NodeType_TIMER, NodeTypeInheritance_TIMER},
    {NodeType_NODE2D, NodeTypeInheritance_NODE2D},
    {NodeType_SPRITE, NodeTypeInheritance_SPRITE},
    {NodeType_ANIMATED_SPRITE, NodeTypeInheritance_ANIMATED_SPRITE},
    {NodeType_TEXT_LABEL, NodeTypeInheritance_TEXT_LABEL},
    {NodeType_COLLISION_SHAPE2D, NodeTypeInheritance_COLLISION_SHAPE2D},
    {NodeType_SPATIAL, NodeTypeInheritance_SPATIAL},
    {NodeType_TEXTURE_CUBE, NodeTypeInheritance_TEXTURE_CUBE},
    {NodeType_DIRECTIONAL_LIGHT, NodeTypeInheritance_DIRECTIONAL_LIGHT},
    {NodeType_POINT_LIGHT, NodeTypeInheritance_POINT_LIGHT},
    {NodeType_SPOT_LIGHT, NodeTypeInheritance_SPOT_LIGHT},
};
