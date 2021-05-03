#ifndef INPUT_ACTION_H
#define INPUT_ACTION_H

#include <vector>
#include <algorithm>

#include <SDL2/SDL.h>

#include "mouse_input.h"
#include "keyboard_input.h"
#include "joystick_input.h"

#include "../utils/logger.h"

using InputTypeFlag = unsigned int;

enum _InputTypeFlag {
    InputTypeFlag_MOUSE = 2,
    InputTypeFlag_KEYBOARD = 4,
    InputTypeFlag_JOYSTICK = 8,
};

class InputAction {
  private:
    MouseAction mouseAction;
    KeyboardAction keyboardAction;
    JoystickAction joystickAction;
    Logger *logger = nullptr;
  public:
    InputTypeFlag inputTypeFlag;
    bool isActionPressed = false;
    bool isActionJustPressed = false;
    bool isActionJustReleased = false;

    InputAction() {
        logger = Logger::GetInstance();
    }

    void AddValue(const std::string &actionValue) {
        if (mouseAction.IsMouseValue(actionValue)) {
            mouseAction.AddValue(actionValue);
        } else if (joystickAction.IsJoystickValue(actionValue)) {
            joystickAction.AddValue(actionValue);
        } else {
            keyboardAction.AddValue(actionValue);
        }
    }

    bool IsActionPressed() {
        if (mouseAction.IsActionPressed()) {
            return true;
        }
        if (keyboardAction.isActionPressed) {
            return true;
        }
        if (joystickAction.IsActionPressed()) {
            return true;
        }
        return false;
    }

    bool IsActionJustPressed() {
        if (mouseAction.IsActionJustPressed()) {
            return true;
        }
        if (keyboardAction.isActionJustPressed) {
            return true;
        }
        if (joystickAction.IsActionJustPressed()) {
            return true;
        }
        return false;
    }

    bool IsActionJustReleased() {
        if (mouseAction.IsActionJustReleased()) {
            return true;
        }
        if (keyboardAction.isActionJustReleased) {
            return true;
        }
        if (joystickAction.IsActionJustReleased()) {
            return true;
        }
        return false;
    }

    void ProcessInputs(const Uint8* keyboardState) {
        keyboardAction.ProcessInputs(keyboardState);
    }

    void ClearInputFlags() {
        keyboardAction.isActionJustPressed = false;
        keyboardAction.isActionJustReleased = false;
    }

};

#endif //INPUT_ACTION_H
