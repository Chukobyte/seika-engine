#ifndef TEXT_RENDERING_ENTITY_SYSTEM_H
#define TEXT_RENDERING_ENTITY_SYSTEM_H

#include "entity_system.h"
#include "../../component/components/transform2D_component.h"
#include "../../component/components/text_label_component.h"
#include "../../../math/space_handler.h"
#include "../../../utils/string_util.h"

class TextRenderingEntitySystem : public EntitySystem {
  private:
    Renderer2D *renderer = nullptr;
    SceneManager *sceneManager = nullptr;
    ComponentManager *componentManager = nullptr;
    CameraManager *cameraManager = nullptr;
    std::unordered_map<Entity, TextLines> textLines = {};

  public:
    TextRenderingEntitySystem() {
        renderer = GD::GetContainer()->renderer2D;
        sceneManager = GD::GetContainer()->sceneManager;
        componentManager = GD::GetContainer()->componentManager;
        cameraManager = GD::GetContainer()->cameraManager;
        enabled = true;
    }

    void Initialize() override {}
    void Enable() override {}
    void Disable() override {}

    void OnRegisterEntity(Entity entity) override {
        EntitySystem::OnRegisterEntity(entity);
        UpdateEntityText(entity, componentManager->GetComponent<TextLabelComponent>(entity));
    }
    void OnUnRegisterEntity(Entity entity) override {
        EntitySystem::OnUnRegisterEntity(entity);
    }

    void OnEntityDestroyed(Entity entity) override {
        textLines.erase(entity);
    }

    void UpdateEntityText(Entity entity, const TextLabelComponent& textLabelComponent) {
        textLines.erase(entity);
        TextLines entityTextLines = StringUtil::ConvertIntoWordWrappedLines(textLabelComponent.text,
                                    textLabelComponent.wordWrap,
                                    textLabelComponent.maxCharactersPerLine);
        textLines.emplace(entity, entityTextLines);
    }

    void Render() {
        if (IsEnabled()) {
            for (Entity entity : entities) {
                Transform2DComponent transform2DComponent = componentManager->GetComponent<Transform2DComponent>(entity);
                Camera2D camera = cameraManager->GetCurrentCamera2D();
                Transform2DComponent parentTransform = SceneNodeHelper::GetCombinedParentsTransforms(sceneManager, componentManager, entity);
                Vector2 textLabelPosition = SpaceHandler::WorldToScreen(transform2DComponent.position + parentTransform.position, transform2DComponent.ignoreCamera);
                TextLabelComponent textLabelComponent = componentManager->GetComponent<TextLabelComponent>(entity);
                Vector2 textLabelScale = !transform2DComponent.ignoreCamera ? transform2DComponent.scale * parentTransform.scale * camera.zoom : transform2DComponent.scale * parentTransform.scale;
                // TODO: Replace with more robust word wrapping
                for (unsigned int i = 0; i < textLines[entity].lines.size(); i++) {
                    renderer->BatchDrawFont(
                        textLabelComponent.font,
                        textLines[entity].lines[i],
                        textLabelPosition.x,
                        textLabelPosition.y + (i * textLabelComponent.font->GetSize()) + (i * textLabelComponent.newLinePadding),
                        transform2DComponent.zIndex,
                        textLabelScale.x,
                        textLabelComponent.color
                    );
                }
            }
        }
    }
};

#endif //TEXT_RENDERING_ENTITY_SYSTEM_H
