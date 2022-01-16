#ifndef ANIMATED_SPRITE_RENDERING_ENTITY_SYSTEM_H
#define ANIMATED_SPRITE_RENDERING_ENTITY_SYSTEM_H

#include "../entity_system.h"
#include "../../component/components/transform2D_component.h"
#include "../../component/components/animated_sprite_component.h"
#include "../../../math/space_handler.h"

class AnimatedSpriteRenderingEntitySystem : public EntitySystem {
  private:
    Renderer2D *renderer = nullptr;
    ComponentManager *componentManager = nullptr;
    CameraManager *cameraManager = nullptr;
    SceneManager *sceneManager = nullptr;

  public:
    AnimatedSpriteRenderingEntitySystem();
    void Render() override;
};

#endif //ANIMATED_SPRITE_RENDERING_ENTITY_SYSTEM_H
