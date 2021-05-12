from roll.node import AnimatedSprite
from roll.input import Input
from roll.engine import Engine
from roll.math import Vector2


class Main(AnimatedSprite):
    def _physics_process(self, delta_time: float) -> None:
        if Input.is_action_just_pressed(action_name="quit"):
            Engine.exit()
        if Input.is_action_pressed(action_name="left"):
            self.add_to_position(Vector2.LEFT())
            self.play(animation_name="Walk")
        elif Input.is_action_pressed(action_name="right"):
            self.add_to_position(Vector2.RIGHT())
            self.play(animation_name="Walk")
        else:
            self.play(animation_name="Idle")
