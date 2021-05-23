#ifndef MATRICES_H
#define MATRICES_H

#include <iostream>

class Matrix4 {
  public:
    float members[16];

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
            members[index] = n1;
            members[index + 4] = n2;
            members[index + 8] = n3;
            members[index + 12] = n4;
        }
    }

    void SetColumn(int index, float n1, float n2, float n3, float n4) {
        if (index >= 0 && index <= 3) {
            members[index] = n1;
            members[index + 1] = n2;
            members[index + 2] = n3;
            members[index + 3] = n4;
        }
    }

    void Set(int row, int col, float value) {
        if (row >= 0 && row <= 3 && col >= 0 && col <= 3) {
            members[(row * 4) + col] = value;
        }
    }

    float Get(int row, int col) {
        return members[(row * 4) + col];
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

    friend std::ostream& operator<<(std::ostream& os, const Matrix4 &v);
};

#endif //MATRICES_H
