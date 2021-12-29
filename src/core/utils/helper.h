#ifndef HELPER_H
#define HELPER_H

#include "../math/vector2.h"

#define GENERATE_ENUM_CLASS_OPERATORS(EnumClass) \
inline EnumClass operator | (EnumClass lhs, EnumClass rhs) { \
using T = std::underlying_type_t <EnumClass>; \
return static_cast<EnumClass>(static_cast<T>(lhs) | static_cast<T>(rhs)); \
} \
\
inline EnumClass& operator |= (EnumClass& lhs, EnumClass rhs) { \
lhs = lhs | rhs; \
return lhs; \
} \
inline EnumClass operator & (EnumClass lhs, EnumClass rhs) { \
using T = std::underlying_type_t <EnumClass>; \
return static_cast<EnumClass>(static_cast<T>(lhs) & static_cast<T>(rhs)); \
} \
\
inline EnumClass& operator &= (EnumClass& lhs, EnumClass rhs) { \
lhs = lhs & rhs; \
return lhs; \
}

class Helper {
  public:
    static float Clamp(const float value, const float min, const float max) {
        if (value < min) {
            return min;
        } else if (value > max) {
            return max;
        }
        return value;
    }

    static Vector2 ClampVector(const Vector2 &value, const Vector2 &min, const Vector2 &max) {
        return ClampVector(value, min.x, min.y, max.x, max.y);
    }

    static Vector2 ClampVector(const Vector2 &value, const float minX, const float minY, const float maxX, const float maxY) {
        return Vector2(
                   Clamp(value.x, minX, maxX),
                   Clamp(value.y, minY, maxY)
               );
    }
};

#endif //HELPER_H
