from roll.node import Node2D, AnimatedSprite
from roll.input import Input
from roll.engine import Engine
from roll.math import Vector2


class Main(Node2D):
    def _start(self) -> None:
        self.player_one_node = self.get_node(name="PlayerOne")

    def _physics_process(self, delta_time: float) -> None:
        if Input.is_action_just_pressed(action_name="quit"):
            Engine.exit()
        if Input.is_action_pressed(action_name="left"):
            self.player_one_node.add_to_position(Vector2.LEFT())
            self.player_one_node.play(animation_name="Walk")
            self.player_one_node.flip_h = True
        elif Input.is_action_pressed(action_name="right"):
            self.player_one_node.add_to_position(Vector2.RIGHT())
            self.player_one_node.play(animation_name="Walk")
            self.player_one_node.flip_h = False
        else:
            self.player_one_node.play(animation_name="Idle")
