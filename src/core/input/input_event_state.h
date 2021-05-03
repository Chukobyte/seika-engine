#ifndef INPUT_EVENT_STATE_H
#define INPUT_EVENT_STATE_H

#include <SDL2/SDL.h>

#include "../math/vector2.h"

struct InputEvent {
    Uint32 eventType;
    // Mouse
    Vector2 mouseMotion;
    bool mousePressed;
    Uint8 mouseButton;
    // Keyboard
    bool keyPressed;
    SDL_Scancode keyScancode;
};

class InputEventState{
public:
    InputEvent ProcessSDLEvent(SDL_Event &event) {
        InputEvent inputEvent;
        switch(event.type) {
            // Mouse
            case SDL_MOUSEMOTION:
                inputEvent.mouseMotion = Vector2(event.motion.x, event.motion.y);
                break;
            case SDL_MOUSEWHEEL:
                break;
            case SDL_MOUSEBUTTONDOWN:
                inputEvent.mousePressed = true;
                inputEvent.mouseButton = event.button.button;
                break;
            case SDL_MOUSEBUTTONUP:
                inputEvent.mousePressed = false;
                inputEvent.mouseButton = event.button.button;
                break;
            // Keyboard
            case SDL_KEYDOWN:
            case SDL_KEYUP:
                inputEvent.keyPressed = event.key.state == SDL_PRESSED;
                inputEvent.keyScancode = event.key.keysym.scancode;
                break;
            default:
                break;
        }
        return inputEvent;
    }
};

#endif //INPUT_EVENT_STATE_H
