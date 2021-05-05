#ifndef CAMERA_MANAGER_H
#define CAMERA_MANAGER_H

#include "camera.h"

class CameraManager {
  private:
    Camera camera = Camera{.id = 1}; // TODO: Make multiple cameras if needed
  public:
    Camera GetCurrentCamera() {
        return camera;
    }

    void UpdateCurrentCamera(Camera updatedCamera) {
        camera = updatedCamera;
    }
};

#endif //CAMERA_MANAGER_H
