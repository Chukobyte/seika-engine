#include "matrices.h"

std::ostream& operator<<(std::ostream& os, const Matrix4 &mat4) {
    os << "[" << mat4.members[0] << ", " << mat4.members[1] << ", " << mat4.members[2] << ", " << mat4.members[3] << "]\n";
    os << "[" << mat4.members[4] << ", " << mat4.members[5] << ", " << mat4.members[6] << ", " << mat4.members[7] << "]\n";
    os << "[" << mat4.members[8] << ", " << mat4.members[9] << ", " << mat4.members[10] << ", " << mat4.members[11] << "]\n";
    os << "[" << mat4.members[12] << ", " << mat4.members[13] << ", " << mat4.members[14] << ", " << mat4.members[15] << "]";
    return os;
}
