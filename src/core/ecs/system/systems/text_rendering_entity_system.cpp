#include "text_rendering_entity_system.h"

TextRenderingEntitySystem::TextRenderingEntitySystem() {
    renderer = GD::GetContainer()->renderer2D;
    sceneManager = GD::GetContainer()->sceneManager;
    componentManager = GD::GetContainer()->componentManager;
    cameraManager = GD::GetContainer()->cameraManager;
    enabled = true;
}

void TextRenderingEntitySystem::OnRegisterEntity(Entity entity) {
    EntitySystem::OnRegisterEntity(entity);
    UpdateEntityText(entity, componentManager->GetComponent<TextLabelComponent>(entity));
}

void TextRenderingEntitySystem::OnEntityDestroyed(Entity entity) {
    EntitySystem::OnEntityDestroyed(entity);
    textLines.erase(entity);
}

void TextRenderingEntitySystem::UpdateEntityText(Entity entity, const TextLabelComponent& textLabelComponent) {
    textLines.erase(entity);
    TextLines entityTextLines = StringUtil::ConvertIntoWordWrappedLines(
                                    textLabelComponent.text,
                                    textLabelComponent.wordWrap,
                                    textLabelComponent.maxCharactersPerLine);
    textLines.emplace(entity, entityTextLines);
}

void TextRenderingEntitySystem::Render() {
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
