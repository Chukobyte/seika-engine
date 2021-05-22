#ifndef QUATERNION_H
#define QUATERNION_H

#include "vector3.h"

class Quaternion {
  public:
    Vector3 v;
    float w;

    Quaternion(float x, float y, float z, float w) : v(Vector3(x, y, z)), w(w) {}

    Quaternion(Vector3 v, float w) : v(v), w(w) {}

    Quaternion operator+(const Quaternion &otherQuaternion) {
        return Quaternion(this->v + otherQuaternion.v, this->w + otherQuaternion.w);
    }

    Quaternion operator-(const Quaternion &otherQuaternion) {
        return Quaternion(this->v - otherQuaternion.v, this->w - otherQuaternion.w);
    }

    Quaternion operator*(const Quaternion &otherQuaternion) {
        float scalar = this->w * otherQuaternion.w - this->v.DotProduct(otherQuaternion.v);
        Vector3 imaginary = otherQuaternion.v * this->w + this->v * otherQuaternion.w + this->v.CrossProduct(otherQuaternion.v);
        return Quaternion(imaginary, scalar);
    }

    double Normalize() {
        float scalar = this->w * this->w;
        float imaginary = this->v * this->v;
        return sqrt(scalar + imaginary);
    }
};

#endif //QUATERNION_H
