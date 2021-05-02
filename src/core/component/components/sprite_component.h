#ifndef SPRITE_COMPONENT_H
#define SPRITE_COMPONENT_H

#include "../component.h"
#include "../../math/rect2.h"
#include "../../rendering/texture.h"

struct SpriteComponent {
    Texture* texture = nullptr;
    Rect2 drawSource;
    Rect2 drawDestination; // Updated when drawing to position
};

#endif //SPRITE_COMPONENT_H
