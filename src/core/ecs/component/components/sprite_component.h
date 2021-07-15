#ifndef SPRITE_COMPONENT_H
#define SPRITE_COMPONENT_H

#include "../component.h"
#include "../../../math/rect2.h"
#include "../../../rendering/texture2d.h"

struct SpriteComponent {
    Texture2D* texture = nullptr;
    Rect2 drawSource;
    bool flipX = false;
    bool flipY = false;
    Color modulate = Color(1.0f, 1.0f, 1.0f, 1.0f);
    Rect2 drawDestination; // Updated when drawing to position
};

#endif //SPRITE_COMPONENT_H
