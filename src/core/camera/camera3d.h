#ifndef CAMERA3D_H
#define CAMERA3D_H

#include "../math/vector2.h"
#include "../math/vector3.h"

struct Camera3D {
    unsigned int id = 0;
    Vector3 position = Vector3(0.0f, 0.0f, 3.0f);
    Vector3 front = Vector3(0.0f, 0.0f, -1.0f);
    Vector3 up = Vector3(0.0f, 1.0f, 0.0f);
    Vector2 zoom = Vector2(1.0f, 1.0f);
    float yaw = -90.0f;
    float pitch = 0.0f;
};

#endif //CAMERA3D_H
