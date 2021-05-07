#ifndef SPACE_HANDLER_H
#define SPACE_HANDLER_H

#include "../global_dependencies.h"

class SpaceHandler {
  public:
    static Vector2 WorldToScreen(Vector2 worldPosition, bool ignoreCamera) {
        if (ignoreCamera) {
            return worldPosition;
        }
        static CameraManager *cameraManager = GD::GetContainer()->cameraManager;
        Camera camera = cameraManager->GetCurrentCamera();
        return (worldPosition - camera.viewport + camera.offset) * camera.zoom;
    }

    static Vector2 ScreenToWorld(Vector2 screenPosition, bool ignoreCamera) {
        if (ignoreCamera) {
            return screenPosition;
        }
        static CameraManager *cameraManager = GD::GetContainer()->cameraManager;
        Camera camera = cameraManager->GetCurrentCamera();
        return (screenPosition - camera.viewport + camera.offset) * camera.zoom;
    }
};

#endif //SPACE_HANDLER_H
