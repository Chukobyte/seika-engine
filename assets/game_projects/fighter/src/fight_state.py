from roll.node import Node
from roll.math import Vector2

from assets.game_projects.fighter.src.input_buffer import InputBuffer


class PlayerStateData:
    def __init__(self, player_node: Node, player_input_buffer: InputBuffer):
        self.player_node = player_node
        self.player_input_buffer = player_input_buffer


class PlayerFrameState:
    def __init__(self, name: str, position: Vector2, inputs: list):
        self.name = name
        self.position = position
        self.inputs = inputs

    def __str__(self):
        return f"name: '{self.name}', position =  '{self.position}', inputs = '{self.inputs}'"

    def __repr__(self):
        return f"name: '{self.name}', position =  '{self.position}', inputs = '{self.inputs}'"


class FrameState:
    def __init__(
        self,
        frame: int,
        player_one_state_data: PlayerStateData,
        player_two_state_data: PlayerStateData,
    ):
        self.frame = frame
        self.player_one_frame_state = None
        self.player_two_frame_state = None

        if player_one_state_data:
            self.player_one_frame_state = PlayerFrameState(
                name="PlayerOne",
                position=player_one_state_data.player_node.position,
                inputs=player_one_state_data.player_input_buffer.values,
            )
        if player_two_state_data:
            self.player_two_frame_state = PlayerFrameState(
                name="PlayerTwo",
                position=player_two_state_data.player_node.position,
                inputs=player_two_state_data.player_input_buffer.values,
            )

    def __str__(self):
        return f"frame: '{self.frame}', player_one_state =  '{self.player_one_frame_state}', player_two_state = '{self.player_two_frame_state}'"

    def __repr__(self):
        return f"frame: '{self.frame}', player_one_state =  '{self.player_one_frame_state}', player_two_state = '{self.player_two_frame_state}'"


class FightState:
    def __init__(self):
        self.frame_states = {}

    def serialize(
        self,
        frame: int,
        player_one_state_data: PlayerStateData,
        player_two_state_data: PlayerStateData,
    ) -> None:
        self.frame_states[frame] = FrameState(
            frame, player_one_state_data, player_two_state_data
        )

    def __str__(self):
        return f"{self.frame_states}"

    def __repr__(self):
        return f"{self.frame_states}"
