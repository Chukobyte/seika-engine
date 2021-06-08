#ifndef VECTOR2_H
#define VECTOR2_H

#include <iostream>
#include <math.h>

class Vector2 {
  public:
    float x;
    float y;

    Vector2(): x(0.0f), y(0.0f) {}

    Vector2(float x, float y): x(x), y(y) {}

    Vector2 operator+(const Vector2 &otherVector) {
        return Vector2(this->x + otherVector.x, this->y + otherVector.y);
    }

    Vector2 operator+=(const Vector2 &otherVector) {
        this->x += otherVector.x;
        this->y += otherVector.y;
        return *this;
    }

    Vector2 operator-(const Vector2 &otherVector) {
        return Vector2(this->x - otherVector.x, this->y - otherVector.y);
    }

    Vector2 operator*(const Vector2 &otherVector) {
        return Vector2(this->x * otherVector.x, this->y * otherVector.y);
    }

    Vector2 operator*=(const Vector2 &otherVector) {
        this->x *= otherVector.x;
        this->y *= otherVector.y;
        return *this;
    }

    Vector2 operator*(float value) {
        return Vector2(this->x * value, this->y * value);
    }

    Vector2 operator/(const Vector2 &otherVector) {
        return Vector2(this->x / otherVector.x, this->y / otherVector.y);
    }

    Vector2 operator/(float value) {
        return Vector2(this->x / value, this->y / value);
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

    Vector2 DotProductVector(const Vector2 &otherVector) {
        return Vector2(DotProduct(otherVector), DotProduct(otherVector));
    }

    Vector2 CrossProduct(const Vector2 &otherVector) {
        return Vector2(this->y - otherVector.y, this->x - otherVector.y);
    }

    double Magnitude() {
        return sqrt(this->x * this->x + this->y * this->y);
    }

    void Normalize() {
        double magnitude = Magnitude();
        this->x = this->x / magnitude;
        this->y = this->y / magnitude;
    }

    Vector2 Lerp(Vector2 otherVector, float amount) {
        return *this + (otherVector - *this) * amount;
    }

    Vector2 ProjectionPlane(Vector2 normalVector) {
        return *this - (normalVector * (this->DotProductVector(normalVector) / (normalVector * normalVector)));
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
