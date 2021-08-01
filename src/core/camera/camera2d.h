#ifndef CAMERA2D_H
#define CAMERA2D_H

#include "../math/vector2.h"
#include "../math/rect2.h"

using CameraMode = unsigned int;

enum _CameraMode {
    CameraMode_FREE = 0,
    CameraMode_FOCUS_ON_NODE = 1,
};

struct Camera2D {
    unsigned int id;
    CameraMode mode = CameraMode_FREE;
    Rect2 boundary = Rect2(-10000000.0f, -10000000.0f, 10000000.0f, 10000000.0f);
    Vector2 viewport = Vector2(0.0f, 0.0f);
    Vector2 zoom = Vector2(1.0f, 1.0f);
    Vector2 offset = Vector2(0.0f, 0.0f);
};

#endif //CAMERA2D_H
