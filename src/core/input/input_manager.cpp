#include "input_manager.h"

InputManager *InputManager::instance = nullptr;

void InputManager::AddAction(const std::string &actionName, const std::string &actionValue) {
    if (inputActions.count(actionName) <= 0) {
        inputActions.emplace(actionName, new InputAction());
    }
    inputActions[actionName]->AddValue(actionValue);
}

void InputManager::RemoveAction(const std::string &actionName) {
    if (inputActions.count(actionName) > 0) {
        delete inputActions[actionName];
        inputActions.erase(actionName);
    }
}

bool InputManager::IsActionPressed(const std::string &actionName) {
    if (inputActions.count(actionName) > 0) {
        return inputActions[actionName]->IsActionPressed();
    }
    return false;
}

bool InputManager::IsActionJustPressed(const std::string &actionName) {
    if (inputActions.count(actionName) > 0) {
        return inputActions[actionName]->IsActionJustPressed();
    }
    return false;
}

bool InputManager::IsActionJustReleased(const std::string &actionName) {
    if (inputActions.count(actionName) > 0) {
        return inputActions[actionName]->IsActionJustReleased();
    }
    return false;
}

void InputManager::ProcessInputs(SDL_Event &event) {
    const Uint8* keyboardState = SDL_GetKeyboardState(NULL);
    mouseInput->ProcessSDLEvent(event);
    for (auto const &pair : inputActions) {
        const std::string &actionName = pair.first;
        InputAction *inputAction = pair.second;
        inputAction->ProcessInputs(keyboardState);
    }
}

void InputManager::ClearInputFlags() {
    mouseInput->ClearInputFlags();
    for (auto const &pair : inputActions) {
        const std::string &actionName = pair.first;
        InputAction *inputAction = pair.second;
        inputAction->ClearInputFlags();
    }
}
