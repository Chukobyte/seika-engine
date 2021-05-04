from roll.node import Node2D
from roll.math import Vector2
from roll.input import Input, Keyboard

class Test(Node2D):
    def _start(self) -> None:
        Input.add_action(action_name="right", value=Keyboard.RIGHT)
        self.start_position = self.get_position()

    def _physics_process(self, delta_time: float) -> None:
        self.add_to_position(Vector2(2.0, 0))
        if self.position.x > 800:
            self.position = Vector2(0, self.start_position.y)

        if Input.is_action_pressed(action_name="right"):
            print("right pressed")

        if Input.is_action_just_pressed(action_name="right"):
            print("right just pressed")

        if Input.is_action_just_released(action_name="right"):
            print("right just released")

    def _end(self) -> None:
        pass
