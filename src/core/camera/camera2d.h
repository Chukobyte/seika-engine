#ifndef CAMERA2D_H
#define CAMERA2D_H

#include "../math/vector2.h"
#include "../math/rect2.h"

enum class CameraMode : int {
    FREE,
    FOCUS_ON_NODE,
};

struct Camera2D {
    unsigned int id;
    CameraMode mode = CameraMode::FREE;
    Rect2 boundary = Rect2(-10000000.0f, -10000000.0f, 10000000.0f, 10000000.0f);
    Vector2 viewport = Vector2(0.0f, 0.0f);
    Vector2 zoom = Vector2(1.0f, 1.0f);
    Vector2 offset = Vector2(0.0f, 0.0f);
};

#endif //CAMERA2D_H
