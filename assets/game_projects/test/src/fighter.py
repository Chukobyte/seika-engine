from roll.engine import Engine
from roll.node import Node2D
from roll.math import Vector2
from roll.input import Input, Keyboard

class Puncher(Node2D):
    def _start(self) -> None:
        Input.add_action(action_name="quit", value=Keyboard.ESC)
        Input.add_action(action_name="right", value=Keyboard.RIGHT)
        Input.add_action(action_name="left", value=Keyboard.LEFT)

    def _physics_process(self, delta_time: float) -> None:
        if Input.is_action_just_pressed(action_name="quit"):
            Engine.exit()

        if Input.is_action_pressed(action_name="right"):
            self.add_to_position(Vector2(1.0, 0))
        elif Input.is_action_pressed(action_name="left"):
            self.add_to_position(Vector2(-1.0, 0))

    def _end(self) -> None:
        pass
