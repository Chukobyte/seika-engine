#ifndef JOYSTICK_INPUT_H
#define JOYSTICK_INPUT_H

#include <SDL2/SDL.h>

const std::string JOYSTICK_BUTTON_A{"joystick_button_a"};
const std::string JOYSTICK_BUTTON_B{"joystick_button_b"};
const std::string JOYSTICK_BUTTON_X{"joystick_button_x"};
const std::string JOYSTICK_BUTTON_Y{"joystick_button_y"};
const std::string JOYSTICK_KEYPAD_UP{"joystick_keypad_up"};
const std::string JOYSTICK_KEYPAD_DOWN{"joystick_keypad_down"};
const std::string JOYSTICK_KEYPAD_RIGHT{"joystick_keypad_right"};
const std::string JOYSTICK_KEYPAD_LEFT{"joystick_keypad_left"};
const std::string JOYSTICK_START{"joystick_start_button"};
const std::string JOYSTICK_BACK{"joystick_back_button"};
const std::string JOYSTICK_LEFT_SHOULDER{"joystick_left_shoulder"};
const std::string JOYSTICK_RIGHT_SHOULDER{"joystick_right_shoulder"};
const std::string JOYSTICK_LEFT_TRIGGER{"joystick_left_trigger"};
const std::string JOYSTICK_RIGHT_TRIGGER{"joystick_right_trigger"};
const std::string JOYSTICK_LEFT_ANALOG{"joystick_left_analog"};
const std::string JOYSTICK_RIGHT_ANALOG{"joystick_right_analog"};
const std::string JOYSTICK_LEFT_ANALOG_UP{"joystick_left_analog_up"};
const std::string JOYSTICK_LEFT_ANALOG_DOWN{"joystick_left_analog_down"};
const std::string JOYSTICK_LEFT_ANALOG_RIGHT{"joystick_left_analog_right"};
const std::string JOYSTICK_LEFT_ANALOG_LEFT{"joystick_left_analog_left"};
const std::string JOYSTICK_RIGHT_ANALOG_UP{"joystick_right_analog_up"};
const std::string JOYSTICK_RIGHT_ANALOG_DOWN{"joystick_right_analog_down"};
const std::string JOYSTICK_RIGHT_ANALOG_RIGHT{"joystick_right_analog_right"};
const std::string JOYSTICK_RIGHT_ANALOG_LEFT{"joystick_right_analog_left"};

static std::map<std::string, SDL_GameControllerButton> ACTION_BUTTON_MAPPINGS = {
    {JOYSTICK_BUTTON_A, SDL_CONTROLLER_BUTTON_A},
    {JOYSTICK_BUTTON_B, SDL_CONTROLLER_BUTTON_B},
    {JOYSTICK_BUTTON_X, SDL_CONTROLLER_BUTTON_X},
    {JOYSTICK_BUTTON_Y, SDL_CONTROLLER_BUTTON_Y},
    {JOYSTICK_KEYPAD_UP, SDL_CONTROLLER_BUTTON_DPAD_UP},
    {JOYSTICK_KEYPAD_DOWN, SDL_CONTROLLER_BUTTON_DPAD_DOWN},
    {JOYSTICK_KEYPAD_LEFT, SDL_CONTROLLER_BUTTON_DPAD_LEFT},
    {JOYSTICK_KEYPAD_RIGHT, SDL_CONTROLLER_BUTTON_DPAD_RIGHT},
    {JOYSTICK_START, SDL_CONTROLLER_BUTTON_START},
    {JOYSTICK_BACK, SDL_CONTROLLER_BUTTON_BACK},
    {JOYSTICK_LEFT_SHOULDER, SDL_CONTROLLER_BUTTON_LEFTSHOULDER},
    {JOYSTICK_RIGHT_SHOULDER, SDL_CONTROLLER_BUTTON_RIGHTSHOULDER},
    {JOYSTICK_LEFT_SHOULDER, SDL_CONTROLLER_BUTTON_LEFTSHOULDER},
    {JOYSTICK_LEFT_ANALOG, SDL_CONTROLLER_BUTTON_LEFTSTICK},
    {JOYSTICK_RIGHT_ANALOG, SDL_CONTROLLER_BUTTON_RIGHTSTICK},
    // Non Game Controller Button Actions
    {JOYSTICK_LEFT_TRIGGER, SDL_CONTROLLER_BUTTON_INVALID},
    {JOYSTICK_RIGHT_TRIGGER, SDL_CONTROLLER_BUTTON_INVALID},
    {JOYSTICK_LEFT_ANALOG_UP, SDL_CONTROLLER_BUTTON_INVALID},
    {JOYSTICK_LEFT_ANALOG_DOWN, SDL_CONTROLLER_BUTTON_INVALID},
    {JOYSTICK_LEFT_ANALOG_RIGHT, SDL_CONTROLLER_BUTTON_INVALID},
    {JOYSTICK_LEFT_ANALOG_LEFT, SDL_CONTROLLER_BUTTON_INVALID},
    {JOYSTICK_RIGHT_ANALOG_UP, SDL_CONTROLLER_BUTTON_INVALID},
    {JOYSTICK_RIGHT_ANALOG_DOWN, SDL_CONTROLLER_BUTTON_INVALID},
    {JOYSTICK_RIGHT_ANALOG_RIGHT, SDL_CONTROLLER_BUTTON_INVALID},
    {JOYSTICK_RIGHT_ANALOG_LEFT, SDL_CONTROLLER_BUTTON_INVALID}
};

//const int JOYSTICK_DEAD_ZONE = 14000;
const int JOYSTICK_TRIGGER_DEAD_ZONE = 8000;

class JoystickAction {
  public:
    bool IsJoystickValue(const std::string &actionValue) {
        return false;
    }

    void AddValue(const std::string &actionValue) {}

    bool IsActionPressed() {
        return false;
    }

    bool IsActionJustPressed() {
        return false;
    }

    bool IsActionJustReleased() {
        return false;
    }

    void ProcessSDLEvent(SDL_Event &event) {
        switch(event.type) {
        case SDL_JOYAXISMOTION:
            // First controller (for now)
            if(event.jaxis.which == 0) {
                // Left Trigger
                if(event.jaxis.axis == 2) {
                    if(event.jaxis.value < -JOYSTICK_TRIGGER_DEAD_ZONE) {
//                            joystickAxisInputManager->ProcessReleased(JOYSTICK_LEFT_TRIGGER);
                    } else if(event.jaxis.value > JOYSTICK_TRIGGER_DEAD_ZONE) {
//                            joystickAxisInputManager->ProcessPressed(JOYSTICK_LEFT_TRIGGER);
                    }
                    // Right Trigger
                } else if(event.jaxis.axis == 5) {
                    if(event.jaxis.value < -JOYSTICK_TRIGGER_DEAD_ZONE) {
//                            joystickAxisInputManager->ProcessReleased(JOYSTICK_RIGHT_TRIGGER);
                    } else if(event.jaxis.value > JOYSTICK_TRIGGER_DEAD_ZONE) {
//                            joystickAxisInputManager->ProcessPressed(JOYSTICK_RIGHT_TRIGGER);
                    }
                }
            }
            break;
        default:
            break;
        }
    }
};

#endif //JOYSTICK_INPUT_H
