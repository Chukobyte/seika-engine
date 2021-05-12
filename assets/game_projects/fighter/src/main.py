from roll.node import Node2D, AnimatedSprite
from roll.input import Input
from roll.engine import Engine
from roll.math import Vector2

from assets.game_projects.fighter.src.input_buffer import InputBuffer


class Main(Node2D):
    def _start(self) -> None:
        self.player_one_input_buffer = InputBuffer()
        self.player_one_node = self.get_node(name="PlayerOne")

    def _physics_process(self, delta_time: float) -> None:
        # INPUTS

        if Input.is_action_just_pressed(action_name="quit"):
            Engine.exit()

        self.player_one_input_buffer.clear()
        self.player_one_input_buffer.poll_client_inputs()

        # SIMULATION

        if self.player_one_input_buffer.is_empty():
            self.player_one_node.play(animation_name="Idle")
        else:
            for input in self.player_one_input_buffer.get_inputs():
                if input == InputBuffer.Value.LEFT:
                    self.player_one_node.add_to_position(Vector2.LEFT())
                    self.player_one_node.play(animation_name="Walk")
                    self.player_one_node.flip_h = True
                elif input == InputBuffer.Value.RIGHT:
                    self.player_one_node.add_to_position(Vector2.RIGHT())
                    self.player_one_node.play(animation_name="Walk")
                    self.player_one_node.flip_h = False
