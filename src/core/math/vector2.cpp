#include "vector2.h"

std::ostream& operator<<(std::ostream& os, const Vector2 &v) {
    os << "(" << v.x << ", " << v.y << ")";
    return os;
}
