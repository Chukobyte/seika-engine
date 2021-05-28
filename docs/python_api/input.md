# seika.input

## Input

Class for handling input.

### Properties

Mouse Action Values

```
Mouse.LEFT_BUTTON = "mb_left"   # Left Mouse Button
Mouse.RIGHT_BUTTON = "mb_right" # Right Mouse Button
```

Keyboard Action Values

```
Keyboard.NUM_0 = 0 # Zero
Keyboard.NUM_1 = 1 # One
Keyboard.NUM_2 = 2 # Two
Keyboard.NUM_3 = 3 # Three
Keyboard.NUM_4 = 4 # Four
Keyboard.NUM_5 = 5 # Five
Keyboard.NUM_6 = 6 # Six
Keyboard.NUM_7 = 7 # Seven
Keyboard.NUM_8 = 8 # Eight
Keyboard.NUM_9 = 9 # Nine

Keyboard.A = "a"
Keyboard.B = "b"
Keyboard.C = "c"
Keyboard.D = "d"
Keyboard.E = "e"
Keyboard.F = "f"
Keyboard.G = "g"
Keyboard.H = "h"
Keyboard.I = "i"
Keyboard.J = "j"
Keyboard.K = "k"
Keyboard.L = "l"
Keyboard.M = "m"
Keyboard.N = "n"
Keyboard.O = "o"
Keyboard.P = "p"
Keyboard.Q = "q"
Keyboard.R = "r"
Keyboard.S = "s"
Keyboard.T = "t"
Keyboard.U = "u"
Keyboard.V = "v"
Keyboard.W = "w"
Keyboard.X = "x"
Keyboard.Y = "y"
Keyboard.Z = "z"

Keyboard.UP = "up"         # Up Arrow Key
Keyboard.DOWN = "down"     # Down Arrow Key
Keyboard.LEFT = "left"     # Left Arrow Key
Keyboard.RIGHT = "right"   # Right Arrow Key
Keyboard.SPACE = "space"   # Space Key
Keyboard.ESC = "esc"       # ESC Key
Keyboard.RETURN = "return" # Enter Key

Keyboard.F1 = "f1"
Keyboard.F2 = "f2"
Keyboard.F3 = "f3"
Keyboard.F4 = "f4"
Keyboard.F5 = "f5"
Keyboard.F6 = "f6"
Keyboard.F7 = "f7"
Keyboard.F8 = "f8"
Keyboard.F9 = "f9"
Keyboard.F10 = "f10"
Keyboard.F11 = "f11"
Keyboard.F12 = "f12"
```

Joystick Action Values

```
Joystick.A_BUTTON = "joystick_button_a" # XBOX A
Joystick.B_BUTTON = "joystick_button_b" # XBOX B
Joystick.X_BUTTON = "joystick_button_x" # XBOX X
Joystick.Y_BUTTON = "joystick_button_y" # XBOX Y

Joystick.KEYPAD_UP = "joystick_keypad_up"
Joystick.KEYPAD_DOWN = "joystick_keypad_down"
Joystick.KEYPAD_LEFT = "joystick_keypad_left"
Joystick.KEYPAD_RIGHT = "joystick_keypad_right"

Joystick.LEFT_ANALOG = "joystick_left_analog"
Joystick.LEFT_ANALOG_LEFT = "joystick_left_analog_left"
Joystick.LEFT_ANALOG_RIGHT = "joystick_left_analog_right"
Joystick.LEFT_ANALOG_UP = "joystick_left_analog_up"
Joystick.LEFT_ANALOG_DOWN = "joystick_left_analog_down"
Joystick.RIGHT_ANALOG = "joystick_right_analog"
Joystick.RIGHT_ANALOG_LEFT = "joystick_right_analog_left"
Joystick.RIGHT_ANALOG_RIGHT = "joystick_right_analog_right"
Joystick.RIGHT_ANALOG_UP = "joystick_right_analog_up"
Joystick.RIGHT_ANALOG_DOWN = "joystick_right_analog_down"

Joystick.START_BUTTON = "joystick_button_start"
Joystick.BACK_BUTTON = "joystick_button_start"

Joystick.SHOULDER_LEFT = "joystick_left_shoulder"
Joystick.SHOULDER_RIGHT = "joystick_right_shoulder"
Joystick.TRIGGER_LEFT = "joystick_left_trigger"
Joystick.TRIGGER_RIGHT = "joystick_right_trigger"
```

---

### Signals

None.

---

### Methods

```python
add_action(action_name: str, value: str) -> None:
```

Adds an input action.  Multiple input values can be added to the same `action_name`.  See [Properties](#properties) for possible values.

```python
remove_action(action_name: str) -> None:
```

Completely removes action.


```python
is_action_pressed(action_name: str) -> bool:
```

Returns true if an action input is currently being held down.

```python
is_action_just_pressed(action_name: str) -> bool:
```

Returns true if an action input was just pressed.

```python
is_action_just_released(action_name: str) -> bool:
```

Returns true if an action input was just released.

---
