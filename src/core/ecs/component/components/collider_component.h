#ifndef COLLIDER_COMPONENT_H
#define COLLIDER_COMPONENT_H

#include <vector>

#include "../component.h"
#include "../../../math/vector2.h"
#include "../../../math/rect2.h"

struct ColliderComponent {
  public:
    Rect2 collider = Rect2();
    std::vector<Entity> collisionExceptions;
    Color color = Color(95.0f / 255.0f, 205.0f / 255.0f, 228.0f / 255.0f, 0.75f);
};

#endif //COLLIDER_COMPONENT_H
