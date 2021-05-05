#ifndef CAMERA_H
#define CAMERA_H

#include "../math/vector2.h"
#include "../math/rect2.h"

using CameraMode = unsigned int;

enum _CameraMode {
    CameraMode_FREE = 0,
    CameraMode_FOCUS_ON_NODE = 1,
};

struct Camera {
    unsigned int id;
    CameraMode mode = CameraMode_FREE;
    Rect2 boundary;
    Vector2 viewport;
    Vector2 zoom = Vector2(1.0f, 1.0f);
    Vector2 offset;
};

#endif //CAMERA_H
