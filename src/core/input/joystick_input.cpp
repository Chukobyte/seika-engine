#include "joystick_input.h"
#include "../project_properties.h"
#include "../utils/archive_loader.h"

JoystickInput *JoystickInput::instance = nullptr;

void JoystickInput::ProcessSDLEvent(InputEvent &inputEvent) {
    switch(inputEvent.sdlType) {
    case SDL_JOYBUTTONDOWN:
    case SDL_JOYBUTTONUP:
        if (inputEvent.controllerId == 0) {
            if (inputEvent.buttonPressed) {
                ProcessButtonPress(inputEvent);
            } else {
                ProcessButtonRelease(inputEvent);
            }
        }
        break;
    case SDL_JOYHATMOTION:
        if (inputEvent.controllerId == 0) {
            ProcessJoyhatMotion(inputEvent);
        }
        break;
    default:
        break;
    }
    ProcessAxisMotion();
}

void JoystickInput::ProcessButtonPress(InputEvent &inputEvent) {
    const std::string &buttonValue = JOYSTICK_BUTTON_TYPE_TO_NAME_MAP[inputEvent.buttonValue];
//    std::cout << "Pressing controller button " << buttonValue << std::endl;
    buttonInputFlags[buttonValue].isPressed = true;
    buttonInputFlags[buttonValue].isJustPressed = true;
}

void JoystickInput::ProcessButtonRelease(InputEvent &inputEvent) {
    const std::string &buttonValue = JOYSTICK_BUTTON_TYPE_TO_NAME_MAP[inputEvent.buttonValue];
//    std::cout << "Releasing controller button " << buttonValue << std::endl;
    buttonInputFlags[buttonValue].isPressed = false;
    buttonInputFlags[buttonValue].isJustReleased = true;
}

void JoystickInput::ProcessJoyhatMotion(InputEvent &inputEvent) {
//    std::cout << "Hat: " << std::to_string(inputEvent.hat) << ", Value: " << std::to_string(inputEvent.hatValue) << std::endl;
    if (inputEvent.hatValue & SDL_HAT_LEFT) {
        if (!buttonInputFlags[JOYSTICK_KEYPAD_LEFT].isPressed) {
            buttonInputFlags[JOYSTICK_KEYPAD_LEFT].isPressed = true;
            buttonInputFlags[JOYSTICK_KEYPAD_LEFT].isJustPressed = true;
        }
    } else {
        if (buttonInputFlags[JOYSTICK_KEYPAD_LEFT].isPressed) {
            buttonInputFlags[JOYSTICK_KEYPAD_LEFT].isPressed = false;
            buttonInputFlags[JOYSTICK_KEYPAD_LEFT].isJustReleased = true;
        }
    }
    if (inputEvent.hatValue & SDL_HAT_RIGHT) {
        if (!buttonInputFlags[JOYSTICK_KEYPAD_RIGHT].isPressed) {
            buttonInputFlags[JOYSTICK_KEYPAD_RIGHT].isPressed = true;
            buttonInputFlags[JOYSTICK_KEYPAD_RIGHT].isJustPressed = true;
        }
    } else {
        if (buttonInputFlags[JOYSTICK_KEYPAD_RIGHT].isPressed) {
            buttonInputFlags[JOYSTICK_KEYPAD_RIGHT].isPressed = false;
            buttonInputFlags[JOYSTICK_KEYPAD_RIGHT].isJustReleased = true;
        }
    }
    if (inputEvent.hatValue & SDL_HAT_UP) {
        if (!buttonInputFlags[JOYSTICK_KEYPAD_UP].isPressed) {
            buttonInputFlags[JOYSTICK_KEYPAD_UP].isPressed = true;
            buttonInputFlags[JOYSTICK_KEYPAD_UP].isJustPressed = true;
        }
    } else {
        if (buttonInputFlags[JOYSTICK_KEYPAD_UP].isPressed) {
            buttonInputFlags[JOYSTICK_KEYPAD_UP].isPressed = false;
            buttonInputFlags[JOYSTICK_KEYPAD_UP].isJustReleased = true;
        }
    }
    if (inputEvent.hatValue & SDL_HAT_DOWN) {
        if (!buttonInputFlags[JOYSTICK_KEYPAD_DOWN].isPressed) {
            buttonInputFlags[JOYSTICK_KEYPAD_DOWN].isPressed = true;
            buttonInputFlags[JOYSTICK_KEYPAD_DOWN].isJustPressed = true;
        }
    } else {
        if (buttonInputFlags[JOYSTICK_KEYPAD_DOWN].isPressed) {
            buttonInputFlags[JOYSTICK_KEYPAD_DOWN].isPressed = false;
            buttonInputFlags[JOYSTICK_KEYPAD_DOWN].isJustReleased = true;
        }
    }
}

void JoystickInput::ProcessAxisMotion() {
    const Uint8 AXIS_MOTION_LEFT_TRIGGER = 2;
    const Uint8 AXIS_MOTION_RIGHT_TRIGGER = 5;

    const Uint8 AXIS_MOTION_LEFT_HORIZONTAL_AXIS = 0;
    const Uint8 AXIS_MOTION_LEFT_VERTICAL_AXIS = 1;
    const Uint8 AXIS_MOTION_RIGHT_HORIZONTAL_AXIS = 3;
    const Uint8 AXIS_MOTION_RIGHT_VERTICAL_AXIS = 4;

    // LEFT AXIS
    // Horizontal
    Sint16 leftHorizontalValue = SDL_JoystickGetAxis(joystickController, AXIS_MOTION_LEFT_HORIZONTAL_AXIS);
    if (leftHorizontalValue < -JOYSTICK_AXIS_DEAD_ZONE) {
        if (!buttonInputFlags[JOYSTICK_LEFT_ANALOG_LEFT].isPressed) {
            buttonInputFlags[JOYSTICK_LEFT_ANALOG_LEFT].isPressed = true;
            buttonInputFlags[JOYSTICK_LEFT_ANALOG_LEFT].isJustPressed = true;
        }
    } else if (leftHorizontalValue > JOYSTICK_AXIS_DEAD_ZONE) {
        if (!buttonInputFlags[JOYSTICK_LEFT_ANALOG_RIGHT].isPressed) {
            buttonInputFlags[JOYSTICK_LEFT_ANALOG_RIGHT].isPressed = true;
            buttonInputFlags[JOYSTICK_LEFT_ANALOG_RIGHT].isJustPressed = true;
        }
    } else {
        if (buttonInputFlags[JOYSTICK_LEFT_ANALOG_LEFT].isPressed) {
            buttonInputFlags[JOYSTICK_LEFT_ANALOG_LEFT].isPressed = false;
            buttonInputFlags[JOYSTICK_LEFT_ANALOG_LEFT].isJustReleased = true;
        }
        if (buttonInputFlags[JOYSTICK_LEFT_ANALOG_RIGHT].isPressed) {
            buttonInputFlags[JOYSTICK_LEFT_ANALOG_RIGHT].isPressed = false;
            buttonInputFlags[JOYSTICK_LEFT_ANALOG_RIGHT].isJustReleased = true;
        }
    }
    // Vertical
    Sint16 leftVerticalValue = SDL_JoystickGetAxis(joystickController, AXIS_MOTION_LEFT_VERTICAL_AXIS);
    if (leftVerticalValue < -JOYSTICK_AXIS_DEAD_ZONE) {
        if (!buttonInputFlags[JOYSTICK_LEFT_ANALOG_UP].isPressed) {
            buttonInputFlags[JOYSTICK_LEFT_ANALOG_UP].isPressed = true;
            buttonInputFlags[JOYSTICK_LEFT_ANALOG_UP].isJustPressed = true;
        }
    } else if (leftVerticalValue > JOYSTICK_AXIS_DEAD_ZONE) {
        if (!buttonInputFlags[JOYSTICK_LEFT_ANALOG_DOWN].isPressed) {
            buttonInputFlags[JOYSTICK_LEFT_ANALOG_DOWN].isPressed = true;
            buttonInputFlags[JOYSTICK_LEFT_ANALOG_DOWN].isJustPressed = true;
        }
    } else {
        if (buttonInputFlags[JOYSTICK_LEFT_ANALOG_UP].isPressed) {
            buttonInputFlags[JOYSTICK_LEFT_ANALOG_UP].isPressed = false;
            buttonInputFlags[JOYSTICK_LEFT_ANALOG_UP].isJustReleased = true;
        }
        if (buttonInputFlags[JOYSTICK_LEFT_ANALOG_DOWN].isPressed) {
            buttonInputFlags[JOYSTICK_LEFT_ANALOG_DOWN].isPressed = false;
            buttonInputFlags[JOYSTICK_LEFT_ANALOG_DOWN].isJustReleased = true;
        }
    }

    // RIGHT AXIS
    // Horizontal
    Sint16 rightHorizontalValue = SDL_JoystickGetAxis(joystickController, AXIS_MOTION_RIGHT_HORIZONTAL_AXIS);
    if (rightHorizontalValue < -JOYSTICK_AXIS_DEAD_ZONE) {
        if (!buttonInputFlags[JOYSTICK_RIGHT_ANALOG_LEFT].isPressed) {
            buttonInputFlags[JOYSTICK_RIGHT_ANALOG_LEFT].isPressed = true;
            buttonInputFlags[JOYSTICK_RIGHT_ANALOG_LEFT].isJustPressed = true;
        }
    } else if (rightHorizontalValue > JOYSTICK_AXIS_DEAD_ZONE) {
        if (!buttonInputFlags[JOYSTICK_RIGHT_ANALOG_RIGHT].isPressed) {
            buttonInputFlags[JOYSTICK_RIGHT_ANALOG_RIGHT].isPressed = true;
            buttonInputFlags[JOYSTICK_RIGHT_ANALOG_RIGHT].isJustPressed = true;
        }
    } else {
        if (buttonInputFlags[JOYSTICK_RIGHT_ANALOG_LEFT].isPressed) {
            buttonInputFlags[JOYSTICK_RIGHT_ANALOG_LEFT].isPressed = false;
            buttonInputFlags[JOYSTICK_RIGHT_ANALOG_LEFT].isJustReleased = true;
        }
        if (buttonInputFlags[JOYSTICK_RIGHT_ANALOG_RIGHT].isPressed) {
            buttonInputFlags[JOYSTICK_RIGHT_ANALOG_RIGHT].isPressed = false;
            buttonInputFlags[JOYSTICK_RIGHT_ANALOG_RIGHT].isJustReleased = true;
        }
    }
    // Vertical
    Sint16 rightVerticalValue = SDL_JoystickGetAxis(joystickController, AXIS_MOTION_RIGHT_VERTICAL_AXIS);
    if (rightVerticalValue < -JOYSTICK_AXIS_DEAD_ZONE) {
        if (!buttonInputFlags[JOYSTICK_RIGHT_ANALOG_UP].isPressed) {
            buttonInputFlags[JOYSTICK_RIGHT_ANALOG_UP].isPressed = true;
            buttonInputFlags[JOYSTICK_RIGHT_ANALOG_UP].isJustPressed = true;
        }
    } else if (rightVerticalValue > JOYSTICK_AXIS_DEAD_ZONE) {
        if (!buttonInputFlags[JOYSTICK_RIGHT_ANALOG_DOWN].isPressed) {
            buttonInputFlags[JOYSTICK_RIGHT_ANALOG_DOWN].isPressed = true;
            buttonInputFlags[JOYSTICK_RIGHT_ANALOG_DOWN].isJustPressed = true;
        }
    } else {
        if (buttonInputFlags[JOYSTICK_RIGHT_ANALOG_UP].isPressed) {
            buttonInputFlags[JOYSTICK_RIGHT_ANALOG_UP].isPressed = false;
            buttonInputFlags[JOYSTICK_RIGHT_ANALOG_UP].isJustReleased = true;
        }
        if (buttonInputFlags[JOYSTICK_RIGHT_ANALOG_DOWN].isPressed) {
            buttonInputFlags[JOYSTICK_RIGHT_ANALOG_DOWN].isPressed = false;
            buttonInputFlags[JOYSTICK_RIGHT_ANALOG_DOWN].isJustReleased = true;
        }
    }

    // Left Trigger
    Sint16 leftTriggerValue = SDL_JoystickGetAxis(joystickController, AXIS_MOTION_LEFT_TRIGGER);
    if (leftTriggerValue < -JOYSTICK_TRIGGER_DEAD_ZONE) {
        if (buttonInputFlags[JOYSTICK_LEFT_TRIGGER].isPressed) {
            buttonInputFlags[JOYSTICK_LEFT_TRIGGER].isPressed = false;
            buttonInputFlags[JOYSTICK_LEFT_TRIGGER].isJustReleased = true;
        }
    } else if (leftTriggerValue > JOYSTICK_TRIGGER_DEAD_ZONE) {
        if (!buttonInputFlags[JOYSTICK_LEFT_TRIGGER].isPressed) {
            buttonInputFlags[JOYSTICK_LEFT_TRIGGER].isPressed = true;
            buttonInputFlags[JOYSTICK_LEFT_TRIGGER].isJustPressed = true;
        }
    }
    // Right Trigger
    Sint16 rightTriggerValue = SDL_JoystickGetAxis(joystickController, AXIS_MOTION_RIGHT_TRIGGER);
    if (rightTriggerValue < -JOYSTICK_TRIGGER_DEAD_ZONE) {
        if (buttonInputFlags[JOYSTICK_RIGHT_TRIGGER].isPressed) {
            buttonInputFlags[JOYSTICK_RIGHT_TRIGGER].isPressed = false;
            buttonInputFlags[JOYSTICK_RIGHT_TRIGGER].isJustReleased = true;
        }
    } else if (rightTriggerValue > JOYSTICK_TRIGGER_DEAD_ZONE) {
        if (!buttonInputFlags[JOYSTICK_RIGHT_TRIGGER].isPressed) {
            buttonInputFlags[JOYSTICK_RIGHT_TRIGGER].isPressed = true;
            buttonInputFlags[JOYSTICK_RIGHT_TRIGGER].isJustPressed = true;
        }
    }
}

void JoystickInput::LoadJoysticks() {
    int result;
    ProjectProperties *projectProperties = ProjectProperties::GetInstance();
    if (projectProperties->isAssetsInMemory) {
        ArchiveLoader *archiveLoader = ArchiveLoader::GetInstance();
        Archive gameControllerDBArchive = archiveLoader->Load("assets/resources/game_controller_db.txt");
        result = SDL_GameControllerAddMappingsFromRW(
                     SDL_RWFromMem(gameControllerDBArchive.fileBuffer, gameControllerDBArchive.fileBufferSize),
                     1
                 );
    } else {
        result = SDL_GameControllerAddMappingsFromFile("assets/resources/game_controller_db.txt");
    }
    assert(result != -1 && "Cannot find game controller db text file!");
    // TODO: Handle more than one controller
    if (SDL_NumJoysticks() > 0) {
        joystickController = SDL_JoystickOpen(0);
        assert(joystickController != nullptr && "JoystickController didn't properly load!");
        gameController = SDL_GameControllerOpen(0);
        assert(gameController != nullptr && "GameController didn't properly load!");
//        std::cout << "Controller loaded!\n";
    } else {
//        std::cout << "Controller didn't loaded!\n";
    }
}

void JoystickInput::ClearInputFlags() {
    for (const auto &pair : buttonInputFlags) {
        buttonInputFlags[pair.first].isJustPressed = false;
        buttonInputFlags[pair.first].isJustReleased = false;
    }
}

bool JoystickInput::IsJoystickValue(const std::string &value) const {
    return buttonInputFlags.count(value) > 0;
}
