#ifndef ANIMATION_H
#define ANIMATION_H

#include <map>

#include "../rendering/texture.h"
#include "../math/rect2.h"

struct AnimationFrame {
    Texture *texture = nullptr;
    Rect2 drawSource;
    int frame;
};

struct Animation {
    std::string name;
    int speed;
    std::map<unsigned int, AnimationFrame> animationFrames;
    unsigned int frames; // Caches number of frames to system doesn't have to count elements of map
};

#endif //ANIMATION_H
