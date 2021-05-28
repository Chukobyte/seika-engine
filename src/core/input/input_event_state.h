#ifndef INPUT_EVENT_STATE_H
#define INPUT_EVENT_STATE_H

#include <SDL2/SDL.h>

#include "../math/vector2.h"

using InputEventType = std::uint32_t;

enum _InputEventType {
    InputEventType_MOUSE = 2,
    InputEventType_KEYBOARD = 4,
    InputEventType_JOYSTICK = 8,
};

struct InputEvent {
    InputEventType type;
    Uint32 sdlType;
    // Mouse
    Vector2 mouseMotion;
    bool mousePressed;
    Uint8 mouseButton;
    // Joystick
    Uint8 controllerId;
    Uint8 axis;
    Sint16 buttonValue;
    bool buttonPressed = false;
    Uint8 hat;
    Uint8 hatValue;
    // Keyboard
    bool keyPressed;
    SDL_Scancode keyScancode;
};

class InputEventState {
  public:
    InputEvent ProcessSDLEvent(SDL_Event &event) {
        InputEvent inputEvent;
        inputEvent.sdlType = event.type;
        switch(event.type) {
        // Mouse
        case SDL_MOUSEMOTION:
            inputEvent.type = InputEventType_MOUSE;
            inputEvent.mouseMotion = Vector2(event.motion.x, event.motion.y);
            break;
        case SDL_MOUSEWHEEL:
            inputEvent.type = InputEventType_MOUSE;
            break;
        case SDL_MOUSEBUTTONDOWN:
            inputEvent.type = InputEventType_MOUSE;
            inputEvent.mousePressed = true;
            inputEvent.mouseButton = event.button.button;
            break;
        case SDL_MOUSEBUTTONUP:
            inputEvent.type = InputEventType_MOUSE;
            inputEvent.mousePressed = false;
            inputEvent.mouseButton = event.button.button;
            break;
        // Joystick
        case SDL_JOYAXISMOTION:
            inputEvent.type = InputEventType_JOYSTICK;
            inputEvent.controllerId = event.jaxis.which;
            inputEvent.axis = event.jaxis.axis;
            inputEvent.buttonValue = event.jaxis.value;
            break;
        case SDL_JOYBUTTONDOWN:
        case SDL_JOYBUTTONUP:
            inputEvent.type = InputEventType_JOYSTICK;
            inputEvent.controllerId = event.jbutton.which;
            inputEvent.buttonValue = event.jbutton.button;
            inputEvent.buttonPressed = event.jbutton.state == SDL_PRESSED;
            break;
        case SDL_JOYHATMOTION:
            inputEvent.type = InputEventType_JOYSTICK;
            inputEvent.controllerId = event.jhat.which;
            inputEvent.hat = event.jhat.hat;
            inputEvent.hatValue = event.jhat.value;
            break;
        // Keyboard
        case SDL_KEYDOWN:
        case SDL_KEYUP:
            if (!event.key.repeat) {
                inputEvent.type = InputEventType_KEYBOARD;
                inputEvent.keyPressed = event.key.state == SDL_PRESSED;
                inputEvent.keyScancode = event.key.keysym.scancode;
            }
            break;
        default:
            break;
        }
        return inputEvent;
    }
};

#endif //INPUT_EVENT_STATE_H
