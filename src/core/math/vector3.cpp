#include "vector3.h"

std::ostream& operator<<(std::ostream& os, const Vector3 &v) {
    os << "(" << v.x << ", " << v.y << ", " << v.z <<  ")";
    return os;
}
