#ifndef MATH_UTIL_H
#define MATH_UTIL_H

class MathUtil {
  public:
    static const float PI;
    static const float DEG2RAD;
    static const float RAD2DEG;
    static const float EPSILON;

    static float Lerp(float source, float destination, float amount) {
        return source + (destination - source) * amount;
    }
};

#endif //MATH_UTIL_H
