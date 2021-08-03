#ifndef VECTOR3_H
#define VECTOR3_H

#include <iostream>
#include <math.h>

#include <glm/glm.hpp>

#include "../color.h"

class Vector3 {
  public:
    float x;
    float y;
    float z;

    Vector3(): x(0.0f), y(0.0f), z(0.0f) {}

    Vector3(float value): x(value), y(value), z(value) {}

    Vector3(float x, float y, float z): x(x), y(y), z(z) {}

    Vector3 operator+(const Vector3 &otherVector) {
        return Vector3(this->x + otherVector.x, this->y + otherVector.y, this->z + otherVector.z);
    }

    Vector3 operator+=(const Vector3 &otherVector) {
        this->x += otherVector.x;
        this->y += otherVector.y;
        this->z += otherVector.z;
        return *this;
    }

    Vector3 operator+=(const glm::vec3 &otherVector) {
        this->x += otherVector.x;
        this->y += otherVector.y;
        this->z += otherVector.z;
        return *this;
    }

    Vector3 operator-(const Vector3 &otherVector) {
        return Vector3(this->x - otherVector.x, this->y - otherVector.y, this->z - otherVector.z);
    }

    Vector3 operator-=(const Vector3 &otherVector) {
        this->x -= otherVector.x;
        this->y -= otherVector.y;
        this->z -= otherVector.z;
        return *this;
    }

    Vector3 operator-=(const glm::vec3 &otherVector) {
        this->x -= otherVector.x;
        this->y -= otherVector.y;
        this->z -= otherVector.z;
        return *this;
    }

    Vector3 operator*(const Vector3 &otherVector) {
        return Vector3(this->x * otherVector.x, this->y * otherVector.y, this->z * otherVector.z);
    }

    Vector3 operator/(const Vector3 &otherVector) {
        return Vector3(this->x / otherVector.x, this->y / otherVector.y, this->z / otherVector.z);
    }

    Vector3 operator*(float value) {
        return Vector3(this->x * value, this->y * value, this->z * value);
    }

    Vector3 operator/(float value) {
        return Vector3(this->x / value, this->y / value, this->z / value);
    }

    Vector3 operator/=(float value) {
        return Vector3(this->x / value, this->y / value, this->z / value);
    }

    bool operator==(const Vector3 &otherVector) const {
        return this->x == otherVector.x && this->y == otherVector.y && this->z == otherVector.z;
    }

    bool operator!=(const Vector3 &otherVector) const {
        return !(*this == otherVector);
    }

    Vector3 operator=(const Color &color) {
        this->x = color.r;
        this->y = color.g;
        this->z = color.b;
        return *this;
    }

    float DotProduct(const Vector3 &otherVector) {
        return (this->x * otherVector.x) + (this->y * otherVector.y) + (this->z * otherVector.z);
    }

    Vector3 CrossProduct(const Vector3 &otherVector) {
        return Vector3(this->y * otherVector.z - this->z * otherVector.y,
                       this->z * otherVector.x - this->x * otherVector.z,
                       this->x * otherVector.y - this->y * otherVector.x);
    }

    double Magnitude() {
        return sqrt((this->x * this->x) + (this->y * this->y) + (this->z * this->z));
    }

    void Normalize() {
        double magnitude = Magnitude();
        this->x = this->x / magnitude;
        this->y = this->y / magnitude;
        this->z = this->z / magnitude;
    }

    Vector3 Lerp(Vector3 otherVector, float amount) {
        return *this + (otherVector - *this) * Vector3(amount, amount, amount);
    }

    glm::vec3 ToGLM() {
        return glm::vec3(x, y, z);
    }

    friend std::ostream& operator<<(std::ostream& os, const Vector3 &v);
};

#endif //VECTOR3_H
