#ifndef COLLIDER_COMPONENT_H
#define COLLIDER_COMPONENT_H

#include "../component.h"
#include "../../../math/vector2.h"
#include "../../../math/rect2.h"

struct ColliderComponent {
  public:
    Rect2 collider;
    Vector2 offset;
};

#endif //COLLIDER_COMPONENT_H
