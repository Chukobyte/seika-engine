from seika.node import Node
from seika.input import Input
from seika.engine import Engine


class Main(Node):
    def _start(self) -> None:
        print("No game project selected, running default gamepad input test...")

    def _physics_process(self, delta_time: float) -> None:
        if Input.is_action_just_pressed(action_name="quit"):
            Engine.exit()

        self._process_analog_inputs()
        self._process_keypad_inputs()
        self._process_shoulder_inputs()
        self._process_trigger_inputs()
        self._process_button_inputs()

    def _process_analog_inputs(self) -> None:
        if Input.is_action_pressed(action_name="a_left_left"):
            print("Left Analog pressed left")
        if Input.is_action_just_pressed(action_name="a_left_left"):
            print("Left Analog just pressed left")
        if Input.is_action_just_released(action_name="a_left_left"):
            print("Left Analog just released left")

        if Input.is_action_pressed(action_name="a_left_right"):
            print("Left Analog pressed right")
        if Input.is_action_just_pressed(action_name="a_left_right"):
            print("Left Analog just pressed right")
        if Input.is_action_just_released(action_name="a_left_right"):
            print("Left Analog just released right")

        if Input.is_action_pressed(action_name="a_left_up"):
            print("Left Analog pressed up")
        if Input.is_action_just_pressed(action_name="a_left_up"):
            print("Left Analog just pressed up")
        if Input.is_action_just_released(action_name="a_left_up"):
            print("Left Analog just released up")

        if Input.is_action_pressed(action_name="a_left_down"):
            print("Left Analog pressed down")
        if Input.is_action_just_pressed(action_name="a_left_down"):
            print("Left Analog just pressed down")
        if Input.is_action_just_released(action_name="a_left_down"):
            print("Left Analog just released down")

        if Input.is_action_pressed(action_name="a_right_left"):
            print("Right Analog pressed left")
        if Input.is_action_just_pressed(action_name="a_right_left"):
            print("Right Analog just pressed left")
        if Input.is_action_just_released(action_name="a_right_left"):
            print("Right Analog just released left")

        if Input.is_action_pressed(action_name="a_right_right"):
            print("Right Analog pressed right")
        if Input.is_action_just_pressed(action_name="a_right_right"):
            print("Right Analog just pressed right")
        if Input.is_action_just_released(action_name="a_right_right"):
            print("Right Analog just released right")

        if Input.is_action_pressed(action_name="a_right_up"):
            print("Right Analog pressed up")
        if Input.is_action_just_pressed(action_name="a_right_up"):
            print("Right Analog just pressed up")
        if Input.is_action_just_released(action_name="a_right_up"):
            print("Right Analog just released up")

        if Input.is_action_pressed(action_name="a_right_down"):
            print("Right Analog pressed down")
        if Input.is_action_just_pressed(action_name="a_right_down"):
            print("Right Analog just pressed down")
        if Input.is_action_just_released(action_name="a_right_down"):
            print("Right Analog just released down")

    def _process_shoulder_inputs(self) -> None:
        if Input.is_action_pressed(action_name="left_shoulder"):
            print("Left Shoulder pressed")
        if Input.is_action_just_pressed(action_name="left_shoulder"):
            print("Left Shoulder just pressed")
        if Input.is_action_just_released(action_name="left_shoulder"):
            print("Left Shoulder just released")

        if Input.is_action_pressed(action_name="right_shoulder"):
            print("Right Shoulder pressed")
        if Input.is_action_just_pressed(action_name="right_shoulder"):
            print("Right Shoulder just pressed")
        if Input.is_action_just_released(action_name="right_shoulder"):
            print("Right Shoulder just released")

    def _process_trigger_inputs(self) -> None:
        if Input.is_action_pressed(action_name="left_trigger"):
            print("Left Trigger pressed")
        if Input.is_action_just_pressed(action_name="left_trigger"):
            print("Left Trigger just pressed")
        if Input.is_action_just_released(action_name="left_trigger"):
            print("Left Trigger just released")

        if Input.is_action_pressed(action_name="right_trigger"):
            print("Right Trigger pressed")
        if Input.is_action_just_pressed(action_name="right_trigger"):
            print("Right Trigger just pressed")
        if Input.is_action_just_released(action_name="right_trigger"):
            print("Right Trigger just released")

    def _process_keypad_inputs(self) -> None:
        if Input.is_action_pressed(action_name="keypad_left"):
            print("Keypad pressed left")
        if Input.is_action_just_pressed(action_name="keypad_left"):
            print("Keypad just pressed left")
        if Input.is_action_just_released(action_name="keypad_left"):
            print("Keypad just released left")

        if Input.is_action_pressed(action_name="keypad_right"):
            print("Keypad pressed right")
        if Input.is_action_just_pressed(action_name="keypad_right"):
            print("Keypad just pressed right")
        if Input.is_action_just_released(action_name="keypad_right"):
            print("Keypad just released right")

        if Input.is_action_pressed(action_name="keypad_up"):
            print("Keypad pressed up")
        if Input.is_action_just_pressed(action_name="keypad_up"):
            print("Keypad just pressed up")
        if Input.is_action_just_released(action_name="keypad_up"):
            print("Keypad just released up")

        if Input.is_action_pressed(action_name="keypad_down"):
            print("Keypad pressed down")
        if Input.is_action_just_pressed(action_name="keypad_down"):
            print("Keypad just pressed down")
        if Input.is_action_just_released(action_name="keypad_down"):
            print("Keypad just released down")

    def _process_button_inputs(self) -> None:
        if Input.is_action_pressed(action_name="button_a"):
            print("Button A pressed")
        if Input.is_action_just_pressed(action_name="button_a"):
            print("Button A just pressed")
        if Input.is_action_just_released(action_name="button_a"):
            print("Button A just released")

        if Input.is_action_pressed(action_name="button_b"):
            print("Button B pressed")
        if Input.is_action_just_pressed(action_name="button_b"):
            print("Button B just pressed")
        if Input.is_action_just_released(action_name="button_b"):
            print("Button B just released")

        if Input.is_action_pressed(action_name="button_x"):
            print("Button X pressed")
        if Input.is_action_just_pressed(action_name="button_x"):
            print("Button X just pressed")
        if Input.is_action_just_released(action_name="button_x"):
            print("Button X just released")

        if Input.is_action_pressed(action_name="button_y"):
            print("Button Y pressed")
        if Input.is_action_just_pressed(action_name="button_y"):
            print("Button Y just pressed")
        if Input.is_action_just_released(action_name="button_y"):
            print("Button Y just released")

        if Input.is_action_pressed(action_name="button_start"):
            print("Button Start pressed")
        if Input.is_action_just_pressed(action_name="button_start"):
            print("Button Start just pressed")
        if Input.is_action_just_released(action_name="button_start"):
            print("Button Start just released")

        if Input.is_action_pressed(action_name="button_back"):
            print("Button Back pressed")
        if Input.is_action_just_pressed(action_name="button_back"):
            print("Button Back just pressed")
        if Input.is_action_just_released(action_name="button_back"):
            print("Button Back just released")

        if Input.is_action_pressed(action_name="left_analog_button"):
            print("Left Analog pressed")
        if Input.is_action_just_pressed(action_name="left_analog_button"):
            print("Left Analog just pressed")
        if Input.is_action_just_released(action_name="left_analog_button"):
            print("Left Analog just released")

        if Input.is_action_pressed(action_name="right_analog_button"):
            print("Right Analog pressed")
        if Input.is_action_just_pressed(action_name="right_analog_button"):
            print("Right Analog just pressed")
        if Input.is_action_just_released(action_name="right_analog_button"):
            print("Right Analog just released")
