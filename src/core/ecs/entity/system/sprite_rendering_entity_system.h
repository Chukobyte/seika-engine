#ifndef SPRITE_RENDERING_ENTITY_SYSTEM_H
#define SPRITE_RENDERING_ENTITY_SYSTEM_H

#include "entity_system.h"
#include "../../component/components/transform2D_component.h"
#include "../../component/components/sprite_component.h"

class SpriteRenderingEntitySystem : public EntitySystem {
  private:
    Renderer *renderer = nullptr;
    ComponentManager *componentManager = nullptr;
  public:
    SpriteRenderingEntitySystem() {
        renderer = GD::GetContainer()->renderer;
        componentManager = GD::GetContainer()->componentManager;
        enabled = true;
    }

    void Enable() override {}
    void Disable() override {}

    void Render() {
        if (IsEnabled()) {
            for (Entity entity : entities) {
                Transform2DComponent transform2DComponent = componentManager->GetComponent<Transform2DComponent>(entity);
                SpriteComponent spriteComponent = componentManager->GetComponent<SpriteComponent>(entity);
                Vector2 drawDestinationPosition = transform2DComponent.position;
                Vector2 drawDestinationSize = Vector2(spriteComponent.drawSource.w * transform2DComponent.scale.x, spriteComponent.drawSource.h * transform2DComponent.scale.y);
                spriteComponent.drawDestination = Rect2(drawDestinationPosition, drawDestinationSize);
                renderer->DrawSprite(spriteComponent.texture, &spriteComponent.drawSource, &spriteComponent.drawDestination, transform2DComponent.zIndex);
            }
        }
    }
};

#endif //SPRITE_RENDERING_ENTITY_SYSTEM_H
