#ifndef TEXTURE_CUBE_RENDERING_ENTITY_SYSTEM_H
#define TEXTURE_CUBE_RENDERING_ENTITY_SYSTEM_H

#include "entity_system.h"
#include "../../component/components/transform2D_component.h"
#include "../../component/components/animated_sprite_component.h"
#include "../../../math/space_handler.h"

class TextureCubeRenderingEntitySystem22 : public EntitySystem {
  private:
    Renderer3D *renderer3D = nullptr;
    ComponentManager *componentManager = nullptr;
    CameraManager *cameraManager = nullptr;
    SceneManager *sceneManager = nullptr;

  public:

    TextureCubeRenderingEntitySystem() {
        renderer3D = GD::GetContainer()->renderer;
        componentManager = GD::GetContainer()->componentManager;
        cameraManager = GD::GetContainer()->cameraManager;
        sceneManager = GD::GetContainer()->sceneManager;
        enabled = true;
    }
    void Initialize() override {}
    void Enable() override {}
    void Disable() override {}

    void UnregisterEntity(Entity entity) override {}

    void Render() {
        if (IsEnabled()) {}
    }
};

#endif //TEXTURE_CUBE_RENDERING_ENTITY_SYSTEM_H
