#ifndef VECTOR4_H
#define VECTOR4_H

#include <iostream>
#include <math.h>

#include <glm/glm.hpp>

#include "../color.h"

class Vector4 {
  public:
    float x;
    float y;
    float z;
    float w;

    Vector4(): x(0.0f), y(0.0f), z(0.0f), w(1.0f) {}

    Vector4(float value): x(value), y(value), z(value), w(1.0f) {}

    Vector4(float x, float y, float z): x(x), y(y), z(z), w(1.0f) {}

    Vector4(float x, float y, float z, float w): x(x), y(y), z(z), w(w) {}

    Vector4 operator+(const Vector4 &otherVector) {
        return Vector4(this->x + otherVector.x, this->y + otherVector.y, this->z + otherVector.z, this->w + otherVector.w);
    }

    Vector4 operator+=(const Vector4 &otherVector) {
        this->x += otherVector.x;
        this->y += otherVector.y;
        this->z += otherVector.z;
        this->w += otherVector.w;
        return *this;
    }

    Vector4 operator+=(const glm::vec4 &otherVector) {
        this->x += otherVector.x;
        this->y += otherVector.y;
        this->z += otherVector.z;
        this->w += otherVector.w;
        return *this;
    }

    Vector4 operator-(const Vector4 &otherVector) {
        return Vector4(this->x - otherVector.x, this->y - otherVector.y, this->z - otherVector.z, this->w - otherVector.w);
    }

    Vector4 operator-=(const Vector4 &otherVector) {
        this->x -= otherVector.x;
        this->y -= otherVector.y;
        this->z -= otherVector.z;
        this->w -= otherVector.w;
        return *this;
    }

    Vector4 operator-=(const glm::vec4 &otherVector) {
        this->x -= otherVector.x;
        this->y -= otherVector.y;
        this->z -= otherVector.z;
        this->w -= otherVector.w;
        return *this;
    }

    Vector4 operator*(const Vector4 &otherVector) {
        return Vector4(this->x * otherVector.x, this->y * otherVector.y, this->z * otherVector.z, this->w * otherVector.w);
    }

    Vector4 operator/(const Vector4 &otherVector) {
        return Vector4(this->x / otherVector.x, this->y / otherVector.y, this->z / otherVector.z, this->w / otherVector.w);
    }

    Vector4 operator*(float value) {
        return Vector4(this->x * value, this->y * value, this->z * value, this->w * value);
    }

    Vector4 operator/(float value) {
        return Vector4(this->x / value, this->y / value, this->z / value, this->w / value);
    }

    Vector4 operator/=(float value) {
        return Vector4(this->x / value, this->y / value, this->z / value, this->w / value);
    }

    bool operator==(const Vector4 &otherVector) const {
        return this->x == otherVector.x && this->y == otherVector.y && this->z == otherVector.z && this->w == otherVector.w;
    }

    bool operator!=(const Vector4 &otherVector) const {
        return !(*this == otherVector);
    }

    double Magnitude() {
        return sqrt((this->x * this->x) + (this->y * this->y) + (this->z * this->z) + (this->w * this->w));
    }

    void Normalize() {
        double magnitude = Magnitude();
        this->x = this->x / magnitude;
        this->y = this->y / magnitude;
        this->z = this->z / magnitude;
        this->w = this->w / magnitude;
    }

    glm::vec4 ToGLM() {
        return glm::vec4(x, y, z, w);
    }

    friend std::ostream& operator<<(std::ostream& os, const Vector4 &v);
};

#endif //VECTOR3_H
