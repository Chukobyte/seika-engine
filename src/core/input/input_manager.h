#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <string>

#include "input_event_state.h"
#include "input_action.h"
#include "mouse_input.h"
#include "keyboard_input.h"
#include "joystick_input.h"

class InputManager {
  private:
    static InputManager *instance;
    InputEventState inputEventState;
    std::map<std::string, InputAction*> inputActions;
    MouseInput *mouseInput = nullptr;

    InputManager();
  public:
    const std::string QUIT_DEFAULT_ACTION = "quit";

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

    void LoadProjectInputActions();

    void AddAction(const std::string &actionName, const std::string &actionValue);
    void RemoveAction(const std::string &actionName);

    bool IsActionPressed(const std::string &actionName);
    bool IsActionJustPressed(const std::string &actionName);
    bool IsActionJustReleased(const std::string &actionName);

    void ProcessInputs(SDL_Event &event);

    void ClearInputFlags();
};

#endif //INPUT_MANAGER_H
