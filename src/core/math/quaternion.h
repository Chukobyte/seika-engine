#ifndef QUATERNION_H
#define QUATERNION_H

#include "vector3.h"
#include "matrices.h"
#include "math_util.h"

class Quaternion {
  public:
    Vector3 v;
    float w;

    Quaternion(float x, float y, float z, float w) : v(Vector3(x, y, z)), w(w) {}

    Quaternion(Vector3 v, float w) : v(v), w(w) {}

    void Rotate(const Vector3 &axis, float angleDegrees) {
        float angleRadians = angleDegrees * MathUtil::DEG2RAD;
        float s = sin(angleRadians / 2);
        v = Vector3(axis.x * s, axis.y * s, axis.z * s);
        w = cos(angleRadians / 2.0f);
    }

    void Normalize() {
        float scalar = this->w * this->w;
        float imaginary = this->v * this->v;
        float n = 1.0f / sqrt(scalar + imaginary);
        v.x *= n;
        v.y *= n;
        v.z *= n;
        w *= n;
    }

    static Matrix4 ToRotationMatrix4(Quaternion quaternion) {
        quaternion.Normalize();
        return Matrix4(
                   1.0f - 2.0f * v.y * v.y - 2.0f * v.z * v.z, 2.0f * v.x * v.y - 2.0f * v.z * w, 2.0f * v.x * v.z + 2.0f * v.y * w, 0.0f,
                   2.0f * v.x * v.y + 2.0f * v.z * w, 1.0f - 2.0f * v.x * v.x - 2.0f * v.z * v.z, 2.0f * v.y * v.z - 2.0f * v.x * w, 0.0f,
                   2.0f * v.x * v.z - 2.0f * v.y * w, 2.0f * v.y * v.z + 2.0f * v.x * w, 1.0f - 2.0f * v.x * v.x - 2.0f * v.y * v.y, 0.0f,
                   0.0f, 0.0f, 0.0f, 1.0f
               );
    }

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
};

#endif //QUATERNION_H
