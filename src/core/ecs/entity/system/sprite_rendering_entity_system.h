#ifndef SPRITE_RENDERING_ENTITY_SYSTEM_H
#define SPRITE_RENDERING_ENTITY_SYSTEM_H

#include "entity_system.h"
#include "../../component/components/transform2D_component.h"
#include "../../component/components/sprite_component.h"
#include "../../../math/space_handler.h"

class SpriteRenderingEntitySystem : public EntitySystem {
  private:
    Renderer *renderer = nullptr;
    ComponentManager *componentManager = nullptr;
    CameraManager *cameraManager = nullptr;
    SceneManager *sceneManager = nullptr;

    Vector2 GetParentPosition(Entity entity) {
        Entity parentEntity = sceneManager->GetParent(entity);
        if (parentEntity == NO_ENTITY) {
            return {0, 0};
        } else {
            Transform2DComponent transform2DComponent = componentManager->GetComponent<Transform2DComponent>(parentEntity);
            return transform2DComponent.position;
        }
    }
  public:
    SpriteRenderingEntitySystem() {
        renderer = GD::GetContainer()->renderer;
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
        if (IsEnabled()) {
            for (Entity entity : entities) {
                Transform2DComponent transform2DComponent = componentManager->GetComponent<Transform2DComponent>(entity);
                SpriteComponent spriteComponent = componentManager->GetComponent<SpriteComponent>(entity);
                Camera camera = cameraManager->GetCurrentCamera();
                Vector2 parentPosition = GetParentPosition(entity);
                Vector2 drawDestinationPosition = SpaceHandler::WorldToScreen(transform2DComponent.position + parentPosition, transform2DComponent.ignoreCamera);
                Vector2 drawScale = !transform2DComponent.ignoreCamera ? transform2DComponent.scale * camera.zoom : transform2DComponent.scale;
                Vector2 drawDestinationSize = Vector2(spriteComponent.drawSource.w * drawScale.x, spriteComponent.drawSource.h * drawScale.y);
                spriteComponent.drawDestination = Rect2(drawDestinationPosition, drawDestinationSize);
                renderer->BatchDrawSprite(
                    spriteComponent.texture,
                    spriteComponent.drawSource,
                    spriteComponent.drawDestination,
                    transform2DComponent.zIndex,
                    0.0f,
                    Color(1.0f, 1.0f, 1.0f),
                    spriteComponent.flipX,
                    spriteComponent.flipY
                );
            }
        }
    }
};

#endif //SPRITE_RENDERING_ENTITY_SYSTEM_H
