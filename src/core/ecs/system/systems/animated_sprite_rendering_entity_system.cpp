#include "animated_sprite_rendering_entity_system.h"

AnimatedSpriteRenderingEntitySystem::AnimatedSpriteRenderingEntitySystem() {
    renderer = GD::GetContainer()->renderer2D;
    componentManager = GD::GetContainer()->componentManager;
    cameraManager = GD::GetContainer()->cameraManager;
    sceneManager = GD::GetContainer()->sceneManager;
    enabled = true;
}

void AnimatedSpriteRenderingEntitySystem::Render() {
    if (IsEnabled()) {
        for (Entity entity : entities) {
            Transform2DComponent transform2DComponent = componentManager->GetComponent<Transform2DComponent>(entity);
            AnimatedSpriteComponent animatedSpriteComponent = componentManager->GetComponent<AnimatedSpriteComponent>(entity);
            Animation currentAnimation = animatedSpriteComponent.currentAnimation;
            AnimationFrame currentFrame = currentAnimation.animationFrames[animatedSpriteComponent.currentFrameIndex];
            if (animatedSpriteComponent.isPlaying) {
                unsigned int newIndex = static_cast<unsigned int>(((SDL_GetTicks() - animatedSpriteComponent.startAnimationTickTime) / currentAnimation.speed) % currentAnimation.frames);
                if (newIndex != animatedSpriteComponent.currentFrameIndex) {
                    // Index changed
                    currentFrame = currentAnimation.animationFrames[newIndex];
                    if (newIndex + 1 == currentAnimation.frames) {
                        // Animation Finished
                        if (!animatedSpriteComponent.loops) {
                            animatedSpriteComponent.isPlaying = false;
                        }
                    }
                    animatedSpriteComponent.currentFrameIndex = newIndex;
                    componentManager->UpdateComponent(entity, animatedSpriteComponent);
                }
            }
            Camera2D camera = cameraManager->GetCurrentCamera2D();
            Transform2DComponent parentTransform = SceneNodeHelper::GetCombinedParentsTransforms(sceneManager, componentManager, entity);
            Vector2 drawDestinationPosition = SpaceHandler::WorldToScreen(transform2DComponent.position + parentTransform.position, transform2DComponent.ignoreCamera);
            Vector2 drawScale = !transform2DComponent.ignoreCamera ? transform2DComponent.scale * parentTransform.scale * camera.zoom : transform2DComponent.scale * parentTransform.scale;
            Vector2 drawDestinationSize = Vector2(currentFrame.drawSource.w * drawScale.x, currentFrame.drawSource.h * drawScale.y);
            Rect2 drawDestination = Rect2(drawDestinationPosition, drawDestinationSize);
            assert(currentFrame.texture != nullptr && "Current frame texture is null");
            renderer->BatchDrawSprite(
                currentFrame.texture,
                currentFrame.drawSource,
                drawDestination,
                transform2DComponent.zIndex,
                transform2DComponent.rotation,
                animatedSpriteComponent.modulate,
                animatedSpriteComponent.flipX,
                animatedSpriteComponent.flipY
            );
        }
    }
}
