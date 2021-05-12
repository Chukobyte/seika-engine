from roll.node import AnimatedSprite
from roll.input import Input


class Main(AnimatedSprite):
    def _physics_process(self, delta_time: float) -> None:
        if Input.is_action_pressed(action_name="left"):
            self.stop()
        elif Input.is_action_pressed(action_name="right"):
            self.play(animation_name="Idle")
