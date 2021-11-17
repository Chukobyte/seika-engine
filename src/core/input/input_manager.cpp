#include "input_manager.h"
#include "../project_properties.h"

InputManager *InputManager::instance = nullptr;

InputManager::InputManager() {
    mouseInput = MouseInput::GetInstance();
    joystickInput = JoystickInput::GetInstance();
}

void InputManager::LoadProjectInputActions() {
    joystickInput->LoadJoysticks();
    ProjectProperties *projectProperties = ProjectProperties::GetInstance();
    InputActionsConfigurations inputActionsConfigurations = projectProperties->GetInputActionsConfigurations();

    for (InputConfiguration inputConfiguration : inputActionsConfigurations.configurations) {
        for (const std::string &inputActionValue : inputConfiguration.values) {
            AddAction(inputConfiguration.name, inputActionValue);
        }
    }
}

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
    InputEvent inputEvent = inputEventState.ProcessSDLEvent(event);
    // TODO: send signal to subscribers for input events

    const Uint8* keyboardState = SDL_GetKeyboardState(NULL);
    mouseInput->ProcessSDLEvent(inputEvent);
    joystickInput->ProcessSDLEvent(inputEvent);
    for (auto const &pair : inputActions) {
        InputAction *inputAction = pair.second;
        inputAction->ProcessInputs(keyboardState);
    }
}

void InputManager::ClearInputFlags() {
    mouseInput->ClearInputFlags();
    joystickInput->ClearInputFlags();
    for (auto const &pair : inputActions) {
        InputAction *inputAction = pair.second;
        inputAction->ClearInputFlags();
    }
}
