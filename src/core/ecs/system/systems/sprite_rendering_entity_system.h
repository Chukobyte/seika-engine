#ifndef SPRITE_RENDERING_ENTITY_SYSTEM_H
#define SPRITE_RENDERING_ENTITY_SYSTEM_H

#include "../entity_system.h"
#include "../../component/components/transform2D_component.h"
#include "../../component/components/sprite_component.h"
#include "../../../math/space_handler.h"

class SpriteRenderingEntitySystem : public EntitySystem {
  private:
    Renderer2D *renderer = nullptr;
    ComponentManager *componentManager = nullptr;
    CameraManager *cameraManager = nullptr;
    SceneManager *sceneManager = nullptr;

  public:
    SpriteRenderingEntitySystem();
    void OnRegisterEntity(Entity entity) override;
    void OnEntityDestroyed(Entity entity) override;
    void Render() override;
};

#endif //SPRITE_RENDERING_ENTITY_SYSTEM_H
