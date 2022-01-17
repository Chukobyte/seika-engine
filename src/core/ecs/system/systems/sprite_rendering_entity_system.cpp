#include "sprite_rendering_entity_system.h"

SpriteRenderingEntitySystem::SpriteRenderingEntitySystem() {
    renderer = GD::GetContainer()->renderer2D;
    componentManager = GD::GetContainer()->componentManager;
    cameraManager = GD::GetContainer()->cameraManager;
    sceneManager = GD::GetContainer()->sceneManager;
    enabled = true;
}

void SpriteRenderingEntitySystem::OnRegisterEntity(Entity entity) {
    EntitySystem::OnRegisterEntity(entity);
    Logger::GetInstance()->Debug("Registering from sprite rendering system entity " + std::to_string(entity));
}

void SpriteRenderingEntitySystem::OnEntityDestroyed(Entity entity) {
    EntitySystem::OnEntityDestroyed(entity);
    entities.erase(entity);
    Logger::GetInstance()->Debug("Removed from sprite rendering system entity " + std::to_string(entity) + ", new count = " + std::to_string(entities.count(entity)));
}

void SpriteRenderingEntitySystem::Render() {
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
                transform2DComponent.rotation,
                spriteComponent.modulate,
                spriteComponent.flipX,
                spriteComponent.flipY
            );
        }
    }
}