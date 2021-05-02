#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <string>

#include "input_action.h"
#include "mouse_input.h"
#include "keyboard_input.h"
#include "joystick_input.h"

class InputManager {
  private:
    static InputManager *instance;
    std::map<std::string, InputAction*> inputActions;
    MouseInput *mouseInput = nullptr;

    InputManager() {
        mouseInput = MouseInput::GetInstance();
    }
  public:
    static InputManager* GetInstance() {
        if (!instance) {
            instance = new InputManager();
        }
        return instance;
    }

    static void ClearInstance() {
        if (instance) {
            delete instance;
            instance = nullptr;
        }
    }

    void AddAction(const std::string &actionName, const std::string &actionValue);
    void RemoveAction(const std::string &actionName);

    bool IsActionPressed(const std::string &actionName);
    bool IsActionJustPressed(const std::string &actionName);
    bool IsActionJustReleased(const std::string &actionName);

    void ProcessInputs(SDL_Event &event);

    void ClearInputFlags();
};

#endif //INPUT_MANAGER_H
