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
    SpriteRenderingEntitySystem() {
        renderer = GD::GetContainer()->renderer2D;
        componentManager = GD::GetContainer()->componentManager;
        cameraManager = GD::GetContainer()->cameraManager;
        sceneManager = GD::GetContainer()->sceneManager;
        enabled = true;
    }

    void Initialize() override {}
    void Enable() override {}
    void Disable() override {}
    void OnEntityDestroyed(Entity entity) override {}

    void Render() override {
        if (IsEnabled()) {
            for (Entity entity : entities) {
                Transform2DComponent transform2DComponent = componentManager->GetComponent<Transform2DComponent>(entity);
                SpriteComponent spriteComponent = componentManager->GetComponent<SpriteComponent>(entity);
                Camera2D camera = cameraManager->GetCurrentCamera2D();
                Transform2DComponent parentTransform = SceneNodeHelper::GetCombinedParentsTransforms(sceneManager, componentManager, entity);
                Vector2 drawDestinationPosition = SpaceHandler::WorldToScreen(transform2DComponent.position + parentTransform.position, transform2DComponent.ignoreCamera);
                Vector2 drawScale = !transform2DComponent.ignoreCamera ? transform2DComponent.scale * parentTransform.scale * camera.zoom : transform2DComponent.scale * parentTransform.scale;
                Vector2 drawDestinationSize = Vector2(spriteComponent.drawSource.w * drawScale.x, spriteComponent.drawSource.h * drawScale.y);
                spriteComponent.drawDestination = Rect2(drawDestinationPosition, drawDestinationSize);
                renderer->BatchDrawSprite(
                    spriteComponent.texture,
                    spriteComponent.drawSource,
                    spriteComponent.drawDestination,
                    transform2DComponent.zIndex,
                    0.0f,
                    spriteComponent.modulate,
                    spriteComponent.flipX,
                    spriteComponent.flipY
                );
            }
        }
    }
};

#endif //SPRITE_RENDERING_ENTITY_SYSTEM_H
