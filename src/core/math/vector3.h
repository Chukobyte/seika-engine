#ifndef VECTOR3_H
#define VECTOR3_H

#include <iostream>
#include <math.h>

class Vector3 {
  public:
    float x;
    float y;
    float z;

    Vector3(): x(0.0f), y(0.0f), z(0.0f) {}

    Vector3(float x, float y, float z): x(x), y(y), z(z) {}

    Vector3 operator+(const Vector3 &otherVector) {
        return Vector3(this->x + otherVector.x, this->y + otherVector.y, this->z + otherVector.z);
    }

    Vector3 operator-(const Vector3 &otherVector) {
        return Vector3(this->x - otherVector.x, this->y - otherVector.y, this->z - otherVector.z);
    }

    Vector3 operator*(const Vector3 &otherVector) {
        return Vector3(this->x * otherVector.x, this->y * otherVector.y,, this->z * otherVector.z);
    }

    Vector3 operator/(const Vector3 &otherVector) {
        return Vector3(this->x / otherVector.x, this->y / otherVector.y,, this->z / otherVector.z);
    }

    bool operator==(const Vector3 &otherVector) const {
        return this->x == otherVector.x && this->y == otherVector.y && this->z == otherVector.z;
    }

    bool operator!=(const Vector3 &otherVector) const {
        return !(*this == otherVector);
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
        return *this + (otherVector - *this) * amount;
    }

    friend std::ostream& operator<<(std::ostream& os, const Vector3 &v);
};

#endif //VECTOR3_H
