#ifndef HELPER_H
#define HELPER_H

#include "../math/vector2.h"

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
