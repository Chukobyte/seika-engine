#ifndef MATRICES_H
#define MATRICES_H

#include <iostream>

#include "math_util.h"
#include "vector3.h"

class Matrix4 {
  private:
    Matrix4 Multiply(const Matrix4 otherMat4) {
        return Matrix4(
                   this->members[0] * otherMat4.members[0] + this->members[1] * otherMat4.members[4] + this->members[2] * otherMat4.members[8] + this->members[3] * otherMat4.members[12],
                   this->members[0] * otherMat4.members[1] + this->members[1] * otherMat4.members[5] + this->members[2] * otherMat4.members[9] + this->members[3] * otherMat4.members[13],
                   this->members[0] * otherMat4.members[2] + this->members[1] * otherMat4.members[6] + this->members[2] * otherMat4.members[10] + this->members[3] * otherMat4.members[14],
                   this->members[0] * otherMat4.members[3] + this->members[1] * otherMat4.members[7] + this->members[2] * otherMat4.members[11] + this->members[3] * otherMat4.members[15],

                   this->members[4] * otherMat4.members[0] + this->members[5] * otherMat4.members[4] + this->members[6] * otherMat4.members[8] + this->members[7] * otherMat4.members[12],
                   this->members[4] * otherMat4.members[1] + this->members[5] * otherMat4.members[5] + this->members[6] * otherMat4.members[9] + this->members[7] * otherMat4.members[13],
                   this->members[4] * otherMat4.members[2] + this->members[5] * otherMat4.members[6] + this->members[6] * otherMat4.members[10] + this->members[7] * otherMat4.members[14],
                   this->members[4] * otherMat4.members[3] + this->members[5] * otherMat4.members[7] + this->members[6] * otherMat4.members[11] + this->members[7] * otherMat4.members[15],

                   this->members[8] * otherMat4.members[0] + this->members[9] * otherMat4.members[4] + this->members[10] * otherMat4.members[8] + this->members[11] * otherMat4.members[12],
                   this->members[8] * otherMat4.members[1] + this->members[9] * otherMat4.members[5] + this->members[10] * otherMat4.members[9] + this->members[11] * otherMat4.members[13],
                   this->members[8] * otherMat4.members[2] + this->members[9] * otherMat4.members[6] + this->members[10] * otherMat4.members[10] + this->members[11] * otherMat4.members[14],
                   this->members[8] * otherMat4.members[3] + this->members[9] * otherMat4.members[7] + this->members[10] * otherMat4.members[11] + this->members[11] * otherMat4.members[15],

                   this->members[12] * otherMat4.members[0] + this->members[13] * otherMat4.members[4] + this->members[14] * otherMat4.members[8] + this->members[15] * otherMat4.members[12],
                   this->members[12] * otherMat4.members[1] + this->members[13] * otherMat4.members[5] + this->members[14] * otherMat4.members[9] + this->members[15] * otherMat4.members[13],
                   this->members[12] * otherMat4.members[2] + this->members[13] * otherMat4.members[6] + this->members[14] * otherMat4.members[10] + this->members[15] * otherMat4.members[14],
                   this->members[12] * otherMat4.members[3] + this->members[13] * otherMat4.members[7] + this->members[14] * otherMat4.members[11] + this->members[15] * otherMat4.members[15]
               );
    }

  public:
    float members[16];

    Matrix4() {
        SetAll(0.0f);
    }

    Matrix4(float n) {
        SetAll(0.0f);
        SetDiagonal(n);
    }

    Matrix4(float a1, float a2, float a3, float a4) {
        SetRow(0, a1, a2, a3, a4);
        SetRow(1, a1, a2, a3, a4);
        SetRow(2, a1, a2, a3, a4);
        SetRow(3, a1, a2, a3, a4);
    }

    Matrix4(float a1, float a2, float a3, float a4,
            float b1, float b2, float b3, float b4,
            float c1, float c2, float c3, float c4,
            float d1, float d2, float d3, float d4) {
        SetRow(0, a1, a2, a3, a4);
        SetRow(1, b1, b2, b3, b4);
        SetRow(2, c1, c2, c3, c4);
        SetRow(3, d1, d2, d3, d4);
    }

    void SetRow(int index, float n1, float n2, float n3, float n4) {
        if (index >= 0 && index <= 3) {
            int setIndex = index * 4;
            members[setIndex] = n1;
            members[setIndex + 1] = n2;
            members[setIndex + 2] = n3;
            members[setIndex + 3] = n4;
        }
    }

    void SetColumn(int index, float n1, float n2, float n3, float n4) {
        if (index >= 0 && index <= 3) {
            int setIndex = index * 4;
            members[setIndex] = n1;
            members[setIndex + 4] = n2;
            members[setIndex + 8] = n3;
            members[setIndex + 12] = n4;
        }
    }

    void SetDiagonal(float n) {
        members[0] = n;
        members[5] = n;
        members[10] = n;
        members[15] = n;
    }

    void Identity() {
        SetAll(0.0f);
        SetDiagonal(1.0f);
    }

    void SetAll(float n) {
        for (unsigned int i = 0; i < sizeof(members); i++) {
            members[i] = n;
        }
    }

    void Set(int row, int col, float value) {
        if (row >= 0 && row <= 3 && col >= 0 && col <= 3) {
            members[(row * 4) + col] = value;
        }
    }

    void Set(const Matrix4 &mat4) {
        for (unsigned int i = 0; i < sizeof(mat4.members); i++) {
            this->members[i] = mat4.members[i];
        }
    }

    float Get(int row, int col) {
        return members[(row * 4) + col];
    }

    Matrix4 Translation(const Vector3 &position) {
        return *this * Matrix4(
                   1.0f, 0.0f, 0.0f, 0.0f,
                   0.0f, 1.0f, 0.0f, 0.0f,
                   0.0f, 0.0f, 1.0f, 0.0f,
                   position.x, position.y, position.z, 1.0f
               );
    }

    Matrix4 Scale(const Vector3 &scaleFactor) {
        Set(0, 0, scaleFactor.x);
        Set(1, 1, scaleFactor.y);
        Set(2, 2, scaleFactor.z);
        return *this;
    }

    Matrix4 Rotate(const Vector3 &axis, float angleDegrees) {
        float x = axis.x;
        float y = axis.y;
        float z = axis.z;

        float c = cos(angleDegrees * MathUtil::DEG2RAD);
        float s = sin(angleDegrees * MathUtil::DEG2RAD);

        Matrix4 rotationMat = Matrix4(x*x*(1.0f-c)+c,   x*y*(1.0f-c)-z*s, x*z*(1.0f-c)+y*s, 0.0f,
                                      y*x*(1.0f-c)+z*s, y*y*(1.0f-c)+c,   y*z*(1.0f-c)-x*s, 0.0f,
                                      z*x*(1.0f-c)-y*s, z*y*(1.0f-c)+x*s, z*z*(1.0f-c)+c,   0.0f,
                                      0.0f,             0.0f,             0.0f,             1.0f);
        return Multiply(rotationMat);
    }

    void ChangeToColumnMajorOrder() {
        Set(Matrix4(
                members[0], members[4], members[8], members[12],
                members[1], members[5], members[9], members[13],
                members[2], members[6], members[10], members[14],
                members[3], members[7], members[11], members[15]
            ));
        std::cout << "Extracted members = \n" << *this << std::endl;
    }

    bool operator==(const Matrix4 &otherMat4) const {
        return this->members[0] == otherMat4.members[0] && this->members[1] == otherMat4.members[1] && this->members[2] == otherMat4.members[2] && this->members[3] == otherMat4.members[3]
               && this->members[4] == otherMat4.members[4] && this->members[5] == otherMat4.members[5] && this->members[6] == otherMat4.members[6] && this->members[7] == otherMat4.members[7]
               && this->members[8] == otherMat4.members[8] && this->members[9] == otherMat4.members[9] && this->members[10] == otherMat4.members[10] && this->members[11] == otherMat4.members[11]
               && this->members[12] == otherMat4.members[12] && this->members[13] == otherMat4.members[13] && this->members[14] == otherMat4.members[14] && this->members[15] == otherMat4.members[15];
    }

    bool operator!=(const Matrix4 &otherMat4) const {
        return !(*this == otherMat4);
    }

    Matrix4 operator+(const Matrix4 &otherMat4) {
        return Matrix4(
                   this->members[0] + otherMat4.members[0], this->members[1] + otherMat4.members[1], this->members[2] + otherMat4.members[2], this->members[3] + otherMat4.members[3],
                   this->members[4] + otherMat4.members[4], this->members[5] + otherMat4.members[5], this->members[6] + otherMat4.members[6], this->members[7] + otherMat4.members[7],
                   this->members[8] + otherMat4.members[8], this->members[9] + otherMat4.members[9], this->members[10] + otherMat4.members[10], this->members[11] + otherMat4.members[11],
                   this->members[12] + otherMat4.members[12], this->members[13] + otherMat4.members[13], this->members[14] + otherMat4.members[14], this->members[15] + otherMat4.members[15]
               );
    }

    Matrix4 operator-(const Matrix4 &otherMat4) {
        return Matrix4(
                   this->members[0] - otherMat4.members[0], this->members[1] - otherMat4.members[1], this->members[2] - otherMat4.members[2], this->members[3] - otherMat4.members[3],
                   this->members[4] - otherMat4.members[4], this->members[5] - otherMat4.members[5], this->members[6] - otherMat4.members[6], this->members[7] - otherMat4.members[7],
                   this->members[8] - otherMat4.members[8], this->members[9] - otherMat4.members[9], this->members[10] - otherMat4.members[10], this->members[11] - otherMat4.members[11],
                   this->members[12] - otherMat4.members[12], this->members[13] - otherMat4.members[13], this->members[14] - otherMat4.members[14], this->members[15] - otherMat4.members[15]
               );
    }

    Matrix4 operator*(const Matrix4 &otherMat4) {
        return Multiply(otherMat4);
    }

    friend std::ostream& operator<<(std::ostream& os, const Matrix4 &v);
};

#endif //MATRICES_H
