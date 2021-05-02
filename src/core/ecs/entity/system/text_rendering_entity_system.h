#ifndef TEXT_RENDERING_ENTITY_SYSTEM_H
#define TEXT_RENDERING_ENTITY_SYSTEM_H

#include "entity_system.h"
#include "../../component/components/transform2D_component.h"
#include "../../component/components/text_label_component.h"

class TextRenderingEntitySystem : public EntitySystem {
  private:
    Renderer *renderer = nullptr;
    ComponentManager *componentManager = nullptr;
  public:
    TextRenderingEntitySystem() {
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
                TextLabelComponent textLabelComponent = componentManager->GetComponent<TextLabelComponent>(entity);
                renderer->DrawFont(textLabelComponent.font, textLabelComponent.text, transform2DComponent.position.x, transform2DComponent.position.y, transform2DComponent.scale.x, textLabelComponent.color);
            }
        }
    }
};

#endif //TEXT_RENDERING_ENTITY_SYSTEM_H
