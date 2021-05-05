#ifndef TEXT_RENDERING_ENTITY_SYSTEM_H
#define TEXT_RENDERING_ENTITY_SYSTEM_H

#include "entity_system.h"
#include "../../component/components/transform2D_component.h"
#include "../../component/components/text_label_component.h"

class TextRenderingEntitySystem : public EntitySystem {
  private:
    Renderer *renderer = nullptr;
    ComponentManager *componentManager = nullptr;
    CameraManager *cameraManager = nullptr;
  public:
    TextRenderingEntitySystem() {
        renderer = GD::GetContainer()->renderer;
        componentManager = GD::GetContainer()->componentManager;
        cameraManager = GD::GetContainer()->cameraManager;
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
                Camera camera = cameraManager->GetCurrentCamera();
                // TODO: fix camera offset applied to textLabelPosition to align y
                Vector2 textLabelPosition = transform2DComponent.position - (!transform2DComponent.ignoreCamera ? (camera.viewport + camera.offset) * camera.zoom * Vector2(1.0, 1.25) : Vector2(0, 0));
                TextLabelComponent textLabelComponent = componentManager->GetComponent<TextLabelComponent>(entity);
                renderer->DrawFont(textLabelComponent.font, textLabelComponent.text, textLabelPosition.x, textLabelPosition.y, transform2DComponent.scale.x * camera.zoom.x, textLabelComponent.color);
            }
        }
    }
};

#endif //TEXT_RENDERING_ENTITY_SYSTEM_H
