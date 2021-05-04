#ifndef KEYBOARD_INPUT_H
#define KEYBOARD_INPUT_H

#include <string>
#include <map>

#include <SDL2/SDL.h>

const std::string KEYBOARD_KEY_UP{"up"};
const std::string KEYBOARD_KEY_DOWN{"down"};
const std::string KEYBOARD_KEY_LEFT{"left"};
const std::string KEYBOARD_KEY_RIGHT{"right"};
const std::string KEYBOARD_KEY_SPACE{"space"};
const std::string KEYBOARD_KEY_ESC{"esc"};
const std::string KEYBOARD_KEY_RETURN{"return"};

static std::map<std::string, SDL_Scancode> KEYBOARD_SCANCODE_TO_VALUE_MAPPING = {
    {"0", SDL_SCANCODE_0},
    {"1", SDL_SCANCODE_1},
    {"2", SDL_SCANCODE_2},
    {"3", SDL_SCANCODE_3},
    {"4", SDL_SCANCODE_4},
    {"5", SDL_SCANCODE_5},
    {"6", SDL_SCANCODE_6},
    {"7", SDL_SCANCODE_7},
    {"8", SDL_SCANCODE_8},
    {"9", SDL_SCANCODE_9},

    {"a", SDL_SCANCODE_A},
    {"b", SDL_SCANCODE_B},
    {"c", SDL_SCANCODE_C},
    {"d", SDL_SCANCODE_D},
    {"e", SDL_SCANCODE_E},
    {"f", SDL_SCANCODE_F},
    {"g", SDL_SCANCODE_G},
    {"h", SDL_SCANCODE_H},
    {"i", SDL_SCANCODE_I},
    {"j", SDL_SCANCODE_J},
    {"k", SDL_SCANCODE_K},
    {"l", SDL_SCANCODE_L},
    {"m", SDL_SCANCODE_M},
    {"n", SDL_SCANCODE_N},
    {"o", SDL_SCANCODE_O},
    {"p", SDL_SCANCODE_P},
    {"q", SDL_SCANCODE_Q},
    {"r", SDL_SCANCODE_R},
    {"s", SDL_SCANCODE_S},
    {"t", SDL_SCANCODE_T},
    {"u", SDL_SCANCODE_U},
    {"v", SDL_SCANCODE_V},
    {"w", SDL_SCANCODE_W},
    {"x", SDL_SCANCODE_X},
    {"y", SDL_SCANCODE_Y},
    {"z", SDL_SCANCODE_Z},

    {KEYBOARD_KEY_LEFT, SDL_SCANCODE_LEFT},
    {KEYBOARD_KEY_RIGHT, SDL_SCANCODE_RIGHT},
    {KEYBOARD_KEY_UP, SDL_SCANCODE_UP},
    {KEYBOARD_KEY_DOWN, SDL_SCANCODE_DOWN},

    {KEYBOARD_KEY_RETURN, SDL_SCANCODE_RETURN},
    {KEYBOARD_KEY_SPACE, SDL_SCANCODE_SPACE},
    {KEYBOARD_KEY_ESC, SDL_SCANCODE_ESCAPE},

    {"f1", SDL_SCANCODE_F1},
    {"f2", SDL_SCANCODE_F2},
    {"f3", SDL_SCANCODE_F3},
    {"f4", SDL_SCANCODE_F4},
    {"f5", SDL_SCANCODE_F5},
    {"f6", SDL_SCANCODE_F6},
    {"f7", SDL_SCANCODE_F7},
    {"f8", SDL_SCANCODE_F8},
    {"f9", SDL_SCANCODE_F9},
    {"f10", SDL_SCANCODE_F10},
    {"f11", SDL_SCANCODE_F11},
    {"f12", SDL_SCANCODE_F12}
};

class KeyboardAction {
  public:
    bool isActionPressed = false;
    bool isActionJustPressed = false;
    bool isActionJustReleased = false;
    std::vector<SDL_Scancode> values;
    SDL_Scancode lastScancodePressed = SDL_SCANCODE_UNKNOWN;

    void AddValue(const std::string &actionValue) {
        if (KEYBOARD_SCANCODE_TO_VALUE_MAPPING.count(actionValue) > 0) {
            SDL_Scancode valueScancode = KEYBOARD_SCANCODE_TO_VALUE_MAPPING[actionValue];
            values.emplace_back(valueScancode);
        }
    }

    void ProcessInputs(const Uint8* keyboardState) {
        for(SDL_Scancode scancodeValue : values) {
//            bool isKeyboardValuePressed = inputEvent.keyScancode == scancodeValue && inputEvent.keyPressed;
            bool isKeyboardValuePressed = keyboardState[scancodeValue];
            if (isKeyboardValuePressed && !isActionPressed) {
                isActionPressed = true;
                isActionJustPressed = true;
                lastScancodePressed = scancodeValue;
                break;
            } else if (!isKeyboardValuePressed && !isActionJustReleased && isActionPressed && scancodeValue == lastScancodePressed) {
                isActionPressed = false;
                isActionJustPressed = false;
                isActionJustReleased = true;
            }
        }
    }
};

#endif //KEYBOARD_INPUT_H
