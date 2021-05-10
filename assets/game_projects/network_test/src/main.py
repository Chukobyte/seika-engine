from roll.node import Node
from roll.input import Input
from roll.engine import Engine


class Main(Node):
    def _start(self) -> None:
        print("Made it to main!")

    def _physics_process(self, delta_time: float) -> None:
        if Input.is_action_just_pressed(action_name="quit"):
            Engine.exit()
