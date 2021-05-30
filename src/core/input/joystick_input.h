#ifndef JOYSTICK_INPUT_H
#define JOYSTICK_INPUT_H

#include <string>
#include <vector>
#include <map>
#include <cassert>
#include <algorithm>

#include <SDL2/SDL.h>

#include "input_event_state.h"

using JoystickButtonType = int;

enum _JoystickButtonType {
    JoystickButtonType_INVALID = -1,
    JoystickButtonType_BUTTON_A = 0,
    JoystickButtonType_BUTTON_B = 1,
    JoystickButtonType_BUTTON_X = 2,
    JoystickButtonType_BUTTON_Y = 3,
    JoystickButtonType_BUTTON_BACK = 6,
    JoystickButtonType_BUTTON_START = 7,
    JoystickButtonType_BUTTON_LEFT_SHOULDER = 4,
    JoystickButtonType_BUTTON_RIGHT_SHOULDER = 5,
    JoystickButtonType_BUTTON_LEFT_AXIS = 8,
    JoystickButtonType_BUTTON_RIGHT_AXIS = 9,
};

const std::string JOYSTICK_BUTTON_A{"joystick_button_a"};
const std::string JOYSTICK_BUTTON_B{"joystick_button_b"};
const std::string JOYSTICK_BUTTON_X{"joystick_button_x"};
const std::string JOYSTICK_BUTTON_Y{"joystick_button_y"};
const std::string JOYSTICK_KEYPAD_UP{"joystick_keypad_up"};
const std::string JOYSTICK_KEYPAD_DOWN{"joystick_keypad_down"};
const std::string JOYSTICK_KEYPAD_RIGHT{"joystick_keypad_right"};
const std::string JOYSTICK_KEYPAD_LEFT{"joystick_keypad_left"};
const std::string JOYSTICK_START{"joystick_button_start"};
const std::string JOYSTICK_BACK{"joystick_button_back"};
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

static std::map<std::string, JoystickButtonType> JOYSTICK_NAME_TO_BUTTON_TYPE_MAP = {
    {JOYSTICK_BUTTON_A, JoystickButtonType_BUTTON_A},
    {JOYSTICK_BUTTON_B, JoystickButtonType_BUTTON_B},
    {JOYSTICK_BUTTON_X, JoystickButtonType_BUTTON_X},
    {JOYSTICK_BUTTON_Y, JoystickButtonType_BUTTON_Y},
    {JOYSTICK_START, JoystickButtonType_BUTTON_START},
    {JOYSTICK_BACK, JoystickButtonType_BUTTON_BACK},
    {JOYSTICK_LEFT_SHOULDER, JoystickButtonType_BUTTON_LEFT_SHOULDER},
    {JOYSTICK_RIGHT_SHOULDER, JoystickButtonType_BUTTON_RIGHT_SHOULDER},
    {JOYSTICK_LEFT_ANALOG, JoystickButtonType_BUTTON_LEFT_AXIS},
    {JOYSTICK_RIGHT_ANALOG, JoystickButtonType_BUTTON_RIGHT_AXIS},
};

static std::map<JoystickButtonType, std::string> JOYSTICK_BUTTON_TYPE_TO_NAME_MAP = {
    {JoystickButtonType_BUTTON_A, JOYSTICK_BUTTON_A},
    {JoystickButtonType_BUTTON_B, JOYSTICK_BUTTON_B},
    {JoystickButtonType_BUTTON_X, JOYSTICK_BUTTON_X},
    {JoystickButtonType_BUTTON_Y, JOYSTICK_BUTTON_Y},
    {JoystickButtonType_BUTTON_START, JOYSTICK_START},
    {JoystickButtonType_BUTTON_BACK, JOYSTICK_BACK},
    {JoystickButtonType_BUTTON_LEFT_SHOULDER, JOYSTICK_LEFT_SHOULDER},
    {JoystickButtonType_BUTTON_RIGHT_SHOULDER, JOYSTICK_RIGHT_SHOULDER},
    {JoystickButtonType_BUTTON_LEFT_AXIS, JOYSTICK_LEFT_ANALOG},
    {JoystickButtonType_BUTTON_RIGHT_AXIS, JOYSTICK_RIGHT_ANALOG},
};

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

const int JOYSTICK_AXIS_DEAD_ZONE = 10000;
const int JOYSTICK_TRIGGER_DEAD_ZONE = 8000;

struct JoystickButtonState {
    bool isPressed = false;
    bool isJustPressed = false;
    bool isJustReleased = false;
};

class JoystickInput {
  private:
    static JoystickInput *instance;
    SDL_Joystick *joystickController = nullptr;
    SDL_GameController *gameController = nullptr;

    std::map<std::string, JoystickButtonState> buttonInputFlags = {
        // Button Process
        {JOYSTICK_BUTTON_B, JoystickButtonState{}},
        {JOYSTICK_BUTTON_A, JoystickButtonState{}},
        {JOYSTICK_BUTTON_X, JoystickButtonState{}},
        {JOYSTICK_BUTTON_Y, JoystickButtonState{}},
        {JOYSTICK_START, JoystickButtonState{}},
        {JOYSTICK_BACK, JoystickButtonState{}},
        {JOYSTICK_LEFT_SHOULDER, JoystickButtonState{}},
        {JOYSTICK_RIGHT_SHOULDER, JoystickButtonState{}},
        {JOYSTICK_LEFT_ANALOG, JoystickButtonState{}},
        {JOYSTICK_RIGHT_ANALOG, JoystickButtonState{}},
        // Hat Process
        {JOYSTICK_KEYPAD_LEFT, JoystickButtonState{}},
        {JOYSTICK_KEYPAD_RIGHT, JoystickButtonState{}},
        {JOYSTICK_KEYPAD_UP, JoystickButtonState{}},
        {JOYSTICK_KEYPAD_DOWN, JoystickButtonState{}},
        // Axis Process
        {JOYSTICK_LEFT_ANALOG_LEFT, JoystickButtonState{}},
        {JOYSTICK_LEFT_ANALOG_RIGHT, JoystickButtonState{}},
        {JOYSTICK_LEFT_ANALOG_UP, JoystickButtonState{}},
        {JOYSTICK_LEFT_ANALOG_DOWN, JoystickButtonState{}},
        {JOYSTICK_RIGHT_ANALOG_LEFT, JoystickButtonState{}},
        {JOYSTICK_RIGHT_ANALOG_RIGHT, JoystickButtonState{}},
        {JOYSTICK_RIGHT_ANALOG_UP, JoystickButtonState{}},
        {JOYSTICK_RIGHT_ANALOG_DOWN, JoystickButtonState{}},
        {JOYSTICK_LEFT_TRIGGER, JoystickButtonState{}},
        {JOYSTICK_RIGHT_TRIGGER, JoystickButtonState{}},
    };

    JoystickInput() {}

    ~JoystickInput() {
        SDL_JoystickClose(joystickController);
        SDL_GameControllerClose(gameController);
    }

    void ProcessButtonPress(InputEvent &inputEvent);

    void ProcessButtonRelease(InputEvent &inputEvent);

    void ProcessJoyhatMotion(InputEvent &inputEvent);

    void ProcessAxisMotion();

  public:
    static JoystickInput* GetInstance() {
        if (!instance) {
            instance = new JoystickInput();
        }
        return instance;
    }
    void ProcessSDLEvent(InputEvent &inputEvent);

    void LoadJoysticks();

    void ClearInputFlags();

    bool IsJoystickValue(const std::string &value) const;

    bool IsActionPressed(const std::string &value) {
        return buttonInputFlags[value].isPressed;
    }

    bool IsActionJustPressed(const std::string &value) {
        return buttonInputFlags[value].isJustPressed;
    }

    bool IsActionJustReleased(const std::string &value) {
        return buttonInputFlags[value].isJustReleased;
    }
};

class JoystickAction {
  private:
    JoystickInput *joystickInput = nullptr;
    std::vector<std::string> joystickValues;
  public:
    JoystickAction() : joystickInput(JoystickInput::GetInstance()) {}

    bool IsJoystickValue(const std::string &actionValue) {
        return joystickInput->IsJoystickValue(actionValue);
    }

    void AddValue(const std::string &actionValue) {
        if (!HasValue(actionValue)) {
            joystickValues.emplace_back(actionValue);
        }
    }

    bool HasValue(const std::string &actionValue) {
        return std::find(joystickValues.begin(), joystickValues.end(), actionValue) != joystickValues.end();
    }

    bool IsActionPressed() {
        for (const std::string &value : joystickValues) {
            if (joystickInput->IsActionPressed(value)) {
                return true;
            }
        }
        return false;
    }

    bool IsActionJustPressed() {
        for (const std::string &value : joystickValues) {
            if (joystickInput->IsActionJustPressed(value)) {
                return true;
            }
        }
        return false;
    }

    bool IsActionJustReleased() {
        for (const std::string &value : joystickValues) {
            if (joystickInput->IsActionJustReleased(value)) {
                return true;
            }
        }
        return false;
    }
};

#endif //JOYSTICK_INPUT_H
