#ifndef TEXT_RENDERING_ENTITY_SYSTEM_H
#define TEXT_RENDERING_ENTITY_SYSTEM_H

#include "entity_system.h"
#include "../../component/components/transform2D_component.h"
#include "../../component/components/text_label_component.h"

class TextRenderingEntitySystem : public EntitySystem {
  private:
    Renderer2D *renderer = nullptr;
    SceneManager *sceneManager = nullptr;
    ComponentManager *componentManager = nullptr;
    CameraManager *cameraManager = nullptr;
  public:
    TextRenderingEntitySystem() {
        renderer = GD::GetContainer()->renderer;
        sceneManager = GD::GetContainer()->sceneManager;
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
                Camera2D camera = cameraManager->GetCurrentCamera2D();
                Transform2DComponent parentTransform = SceneNodeHelper::GetCombinedParentsTransforms(sceneManager, componentManager, entity);
                Vector2 textLabelPosition = SpaceHandler::WorldToScreen(transform2DComponent.position + parentTransform.position, transform2DComponent.ignoreCamera);
                TextLabelComponent textLabelComponent = componentManager->GetComponent<TextLabelComponent>(entity);
                Vector2 textLabelScale = !transform2DComponent.ignoreCamera ? transform2DComponent.scale * parentTransform.scale * camera.zoom : transform2DComponent.scale * parentTransform.scale;
                renderer->BatchDrawFont(
                    textLabelComponent.font,
                    textLabelComponent.text,
                    textLabelPosition.x,
                    textLabelPosition.y,
                    transform2DComponent.zIndex,
                    textLabelScale.x,
                    textLabelComponent.color
                );
            }
        }
    }
};

#endif //TEXT_RENDERING_ENTITY_SYSTEM_H
