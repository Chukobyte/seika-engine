#ifndef MATH_UTIL_H
#define MATH_UTIL_H

class MathUtil {
  public:
    static float Lerp(float source, float destination, float amount) {
        return source + (destination - source) * amount;
    }
};

#endif //MATH_UTIL_H
