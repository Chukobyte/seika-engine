#ifndef VECTOR2_H
#define VECTOR2_H

#include <iostream>

class Vector2 {
  public:
    float x;
    float y;

    Vector2(): x(0.0f), y(0.0f) {}

    Vector2(float x, float y): x(x), y(y) {}

    Vector2 operator+(const Vector2 &otherVector) {
        return Vector2(this->x + otherVector.x, this->y + otherVector.y);
    }

    Vector2 operator-(const Vector2 &otherVector) {
        return Vector2(this->x - otherVector.x, this->y - otherVector.y);
    }

    Vector2 operator*(const Vector2 &otherVector) {
        return Vector2(this->x * otherVector.x, this->y * otherVector.y);
    }

    Vector2 operator/(const Vector2 &otherVector) {
        return Vector2(this->x / otherVector.x, this->y / otherVector.y);
    }

    bool operator==(const Vector2 &otherVector) const {
        return this->x == otherVector.x && this->y == otherVector.y;
    }

    bool operator!=(const Vector2 &otherVector) const {
        return !(*this == otherVector);
    }

    float DotProduct(const Vector2 &otherVector) {
        return (this->x * otherVector.x) + (this->y * otherVector.y);
    }

    friend std::ostream& operator<<(std::ostream& os, const Vector2 &v);
};

class IVector2 {
  public:
    int x;
    int y;

    IVector2(): x(0), y(0) {}

    IVector2(int x, int y): x(x), y(y) {}

    IVector2 operator+(const IVector2 &otherVector) {
        return IVector2(this->x + otherVector.x, this->y + otherVector.y);
    }

    IVector2 operator-(const IVector2 &otherVector) {
        return IVector2(this->x - otherVector.x, this->y - otherVector.y);
    }

    IVector2 operator*(const IVector2 &otherVector) {
        return IVector2(this->x * otherVector.x, this->y * otherVector.y);
    }

    IVector2 operator/(const IVector2 &otherVector) {
        return IVector2(this->x / otherVector.x, this->y / otherVector.y);
    }

    bool operator==(const IVector2 &otherVector) const {
        return this->x == otherVector.x && this->y == otherVector.y;
    }

    bool operator!=(const IVector2 &otherVector) const {
        return !(*this == otherVector);
    }

    float DotProduct(const IVector2 &otherVector) {
        return (this->x * otherVector.x) + (this->y * otherVector.y);
    }

    friend std::ostream& operator<<(std::ostream& os, const IVector2 &v);
};

#endif //VECTOR2_H
