#ifndef RECT2_H
#define RECT2_H

#include <iostream>

#include "vector2.h"

class Rect2 {
  public:
    float x;
    float y;
    float w;
    float h;

    Rect2(): x(0.0f), y(0.0f), w(0.0f), h(0.0f) {}

    Rect2(float x, float y, float w, float h): x(x), y(y), w(w), h(h) {}

    Rect2(float x, float y, Vector2 size): x(x), y(y), w(size.x), h(size.y) {}

    Rect2(Vector2 position, Vector2 size): x(position.x), y(position.y), w(size.x), h(size.y) {}

    Rect2(Vector2 position, float w, float h): x(position.x), y(position.y), w(w), h(h) {}

    bool operator==(const Rect2 &otherRect2) const {
        return this->x == otherRect2.x && this->y == otherRect2.y && this->w == otherRect2.w && this->h == otherRect2.h;
    }

    bool operator!=(const Rect2 &otherRect2) const {
        return !(*this == otherRect2);
    }

    Rect2 operator+(const Vector2 &vector) {
        return Rect2(x + vector.x, y + vector.y, w, h);
    }

    Rect2 operator+=(const Vector2 &vector) {
        x += vector.x;
        y += vector.y;
        return *this;
    }

    Rect2 operator-(const Vector2 &vector) {
        return Rect2(x - vector.x, y - vector.y, w, h);
    }

    Rect2 operator-=(const Vector2 &vector) {
        x -= vector.x;
        y -= vector.y;
        return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const Rect2 &r);
};

#endif //RECT2_H
