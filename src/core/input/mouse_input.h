#ifndef MOUSE_INPUT_H
#define MOUSE_INPUT_H

#include <string>
#include <vector>

#include <SDL2/SDL.h>

#include "../math/vector2.h"

const std::string MOUSE_BUTTON_LEFT{"mb_left"};
const std::string MOUSE_BUTTON_RIGHT{"mb_right"};
const std::string MOUSE_BUTTON_MIDDLE{"mb_middle"};

using MouseEventType = unsigned int;

enum _MouseEventType {
    MouseEventType_MOUSE_BUTTON_LEFT_PRESSED = 0,
    MouseEventType_MOUSE_BUTTON_LEFT_JUST_PRESSED = 1,
    MouseEventType_MOUSE_BUTTON_LEFT_JUST_RELEASED = 2,
    MouseEventType_MOUSE_BUTTON_RIGHT_PRESSED = 3,
    MouseEventType_MOUSE_BUTTON_RIGHT_JUST_PRESSED = 4,
    MouseEventType_MOUSE_BUTTON_RIGHT_JUST_RELEASED = 5,
};

class MouseInput {
  private:
    static MouseInput *instance;
    Vector2 mousePosition;
    MouseInput() {}
  public:
    bool isMouseLeftButtonPressed = false;
    bool isMouseLeftButtonJustPressed = false;
    bool isMouseLeftButtonJustReleased = false;
    bool isMouseRightButtonPressed = false;
    bool isMouseRightButtonJustPressed = false;
    bool isMouseRightButtonJustReleased = false;

    static MouseInput* GetInstance() {
        if (!instance) {
            instance = new MouseInput();
        }
        return instance;
    }

    void ClearInputFlags() {
        isMouseLeftButtonJustPressed = false;
        isMouseRightButtonJustPressed = false;
        isMouseLeftButtonJustReleased = false;
        isMouseRightButtonJustReleased = false;
    }

    Vector2 GetMousePosition() const {
        return mousePosition;
    }

    void ProcessSDLEvent(SDL_Event &event) {
        switch(event.type) {
        // Mouse
        case SDL_MOUSEMOTION:
            mousePosition.x = event.motion.x;
            mousePosition.y = event.motion.y;
            break;
        case SDL_MOUSEWHEEL:
            break;
        case SDL_MOUSEBUTTONDOWN:
            if(event.button.button == SDL_BUTTON_LEFT) {
                isMouseLeftButtonPressed = true;
                isMouseLeftButtonJustPressed = true;
            } else if(event.button.button == SDL_BUTTON_RIGHT) {
                isMouseRightButtonPressed = true;
                isMouseRightButtonJustPressed = true;
            }
            break;
        case SDL_MOUSEBUTTONUP:
            if(event.button.button == SDL_BUTTON_LEFT) {
                isMouseLeftButtonPressed = false;
                isMouseLeftButtonJustPressed = false;
                isMouseLeftButtonJustReleased = true;
            } else if(event.button.button == SDL_BUTTON_RIGHT) {
                isMouseRightButtonPressed = false;
                isMouseRightButtonJustPressed = false;
                isMouseRightButtonJustReleased = true;
            }
            break;
        default:
            break;
        }
    }
};

class MouseAction {
  private:
    std::vector<std::string> mouseValues;
    MouseInput *mouseInput = nullptr;
  public:
    MouseAction() {
        mouseInput = MouseInput::GetInstance();
    }

    static bool IsMouseValue(const std::string &actionValue) {
        if (actionValue == MOUSE_BUTTON_LEFT || actionValue == MOUSE_BUTTON_RIGHT) {
            return true;
        }
        return false;
    }

    void AddValue(const std::string &actionValue) {
        if (!HasValue(actionValue)) {
            mouseValues.emplace_back(actionValue);
        }
    }

    bool HasValue(const std::string &actionValue) {
        for (const std::string &value : mouseValues) {
            if (value == actionValue) {
                return true;
            }
        }
        return false;
    }

    bool IsActionPressed() {
        for (const std::string &value : mouseValues) {
            if ((value == MOUSE_BUTTON_LEFT && mouseInput->isMouseLeftButtonPressed)
                    || (value == MOUSE_BUTTON_RIGHT && mouseInput->isMouseRightButtonPressed)) {
                return true;
            }
        }
        return false;
    }

    bool IsActionJustPressed() {
        for (const std::string &value : mouseValues) {
            if ((value == MOUSE_BUTTON_LEFT && mouseInput->isMouseLeftButtonJustPressed)
                    || (value == MOUSE_BUTTON_RIGHT && mouseInput->isMouseRightButtonJustPressed)) {
                return true;
            }
        }
        return false;
    }

    bool IsActionJustReleased() {
        for (const std::string &value : mouseValues) {
            if ((value == MOUSE_BUTTON_LEFT && mouseInput->isMouseLeftButtonJustReleased)
                    || (value == MOUSE_BUTTON_RIGHT && mouseInput->isMouseRightButtonJustReleased)) {
                return true;
            }
        }
        return false;
    }
};

#endif //MOUSE_INPUT_H
