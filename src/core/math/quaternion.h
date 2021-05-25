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

    void Rotate(float angleDegrees) {
        Rotate(v, angleDegrees);
    }

    void Rotate(const Vector3 &axis, float angleDegrees) {
        float angleRadians = angleDegrees * MathUtil::DEG2RAD;
        float s = sin(angleRadians / 2.0f);
        Quaternion localQuaternion = Quaternion(Vector3(axis.x * s, axis.y * s, axis.z * s), cos(angleRadians / 2.0f));

        *this = localQuaternion * *this;
    }

    void Normalize() {
        float magnitude = sqrt(w * w + v.x * v.x + v.y * v.y + v.z * v.z);
        v /= magnitude;
        w /= magnitude;
    }

    static Matrix4 ToRotationMatrix4(Quaternion q) {
        q.Normalize();
        return Matrix4(
                   1.0f - 2.0f * q.v.y * q.v.y - 2.0f * q.v.z * q.v.z, 2.0f * q.v.x * q.v.y - 2.0f * q.w * q.v.z, 2.0f * q.v.x * q.v.z + 2.0f * q.w * q.v.y, 0.0f,
                   2.0f * q.v.x * q.v.y + 2.0f * q.w * q.v.z, 1.0f - 2.0f * q.v.x * q.v.x - 2.0f * q.v.z * q.v.z, 2.0f * q.v.y * q.v.z + 2.0f * q.w * q.v.x, 0.0f,
                   2.0f * q.v.x * q.v.z - 2.0f * q.w * q.v.y, 2.0f * q.v.y * q.v.z - 2.0f * q.w * q.v.x, 1.0f - 2.0f * q.v.x * q.v.x - 2.0f * q.v.y * q.v.y, 0.0f,
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
        float qx = w * otherQuaternion.v.x + v.x * otherQuaternion.w + v.y * otherQuaternion.v.z - v.z * otherQuaternion.v.y;
        float qy = w * otherQuaternion.v.y - v.x * otherQuaternion.v.z + v.y * otherQuaternion.w + v.z * otherQuaternion.v.x;
        float qz = w * otherQuaternion.v.z + v.x * otherQuaternion.v.y - v.y * otherQuaternion.v.x + v.z * otherQuaternion.w;
        float qw = w * otherQuaternion.w - v.x * otherQuaternion.v.x - v.y * otherQuaternion.v.y - v.z * otherQuaternion.v.z;
        return Quaternion(qx, qy, qz, qw);
    }
};

#endif //QUATERNION_H
