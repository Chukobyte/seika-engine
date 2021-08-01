#ifndef CAMERA_MANAGER_H
#define CAMERA_MANAGER_H

#include "camera2d.h"
#include "camera3d.h"

class CameraManager {
  private:
    Camera2D camera2D = Camera2D{.id = 1}; // TODO: Make multiple cameras if needed
    Camera3D camera3D = Camera3D{.id = 1};
  public:
    Camera2D GetCurrentCamera2D() {
        return camera2D;
    }

    void UpdateCurrentCamera2D(Camera2D updatedCamera) {
        camera2D = updatedCamera;
    }

    Camera3D GetCurrentCamera3D() {
        return camera3D;
    }

    void UpdateCurrentCamera3D(Camera3D updatedCamera) {
        camera3D = updatedCamera;
    }
};

#endif //CAMERA_MANAGER_H
