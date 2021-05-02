#ifndef TRANSFORM_COMPONENT_H
#define TRANSFORM_COMPONENT_H

#include "../component.h"
#include "../../../math/vector2.h"

struct Transform2DComponent {
    Vector2 position = Vector2(0.0f, 0.0f);
    Vector2 scale = Vector2(1.0f, 1.0f);
    float rotation = 0.0f;
    int zIndex = 0;
    bool isZIndexRelativeToParent = true;
};

#endif //TRANSFORM_COMPONENT_H
