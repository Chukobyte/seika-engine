from roll.node import Node2D, AnimatedSprite
from roll.input import Input
from roll.engine import Engine
from roll.math import Vector2

from assets.game_projects.fighter.src.input_buffer import InputBuffer
from assets.game_projects.fighter.src.game_state import GameState, PlayerStateData


class Main(Node2D):
    def _start(self) -> None:
        self.frame_counter = 0
        self.player_one_input_buffer = InputBuffer(
            left_action_name="one_left", right_action_name="one_right"
        )
        self.player_one_node = self.get_node(name="PlayerOne")
        self.player_two_node = self.get_node(name="PlayerTwo")
        self.player_two_input_buffer = InputBuffer(
            left_action_name="two_left", right_action_name="two_right"
        )
        self.game_state = GameState()

    def _physics_process(self, delta_time: float) -> None:
        # INPUTS

        if Input.is_action_just_pressed(action_name="quit"):
            Engine.exit()

        for input_buffer in [
            self.player_one_input_buffer,
            self.player_two_input_buffer,
        ]:
            input_buffer.poll_client_inputs(frame=self.frame_counter)

        # SIMULATION

        self.game_state.simulate_frame(
            frame=self.frame_counter,
            player_one_state_data=PlayerStateData(
                player_node=self.player_one_node,
                player_input_buffer=self.player_one_input_buffer,
            ),
            player_two_state_data=PlayerStateData(
                player_node=self.player_two_node,
                player_input_buffer=self.player_two_input_buffer,
            ),
        )

        # print(self.player_one_input_buffer)
        self.frame_counter += 1
