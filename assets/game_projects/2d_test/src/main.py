from seika.node import Node2D
from seika.input import Input, Mouse
from seika.engine import Engine
from seika.physics import Collision


class Main(Node2D):
    def _start(self) -> None:
        print("2D test start!")

    def _physics_process(self, delta_time: float) -> None:
        if Input.is_action_just_pressed(action_name="quit"):
            Engine.exit()

        if Input.is_action_just_pressed(action_name="mouse_left_click"):
            print(f"collided_node_with_mouse = {Collision.get_nodes_under_mouse()}")
