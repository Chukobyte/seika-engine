#ifndef ANIMATED_SPRITE_COMPONENT_H
#define ANIMATED_SPRITE_COMPONENT_H

#include <map>

#include "../component.h"
#include "../../../animation/animation.h"
#include "../../../math/rect2.h"
#include "../../rendering/texture.h"

struct AnimatedSpriteComponent {
    std::map<std::string, Animation> animations;
    Animation currentAnimation; // Preselects first added animation
    int currentFrameIndex;
    bool isPlaying;
};

#endif //ANIMATED_SPRITE_COMPONENT_H
