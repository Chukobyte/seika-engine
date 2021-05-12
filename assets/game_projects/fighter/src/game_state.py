from roll.node import Node
from roll.math import Vector2

from assets.game_projects.fighter.src.input_buffer import InputBuffer


class PlayerStateData:
    def __init__(self, player_node: Node, player_input_buffer: InputBuffer):
        self.player_node = player_node
        self.player_input_buffer = player_input_buffer


class GameState:
    def simulate_frame(
        self, frame: int, player_one_state_data: PlayerStateData
    ) -> None:
        if player_one_state_data.player_input_buffer.is_empty():
            player_one_state_data.player_node.play(animation_name="Idle")
        else:
            for input in player_one_state_data.player_input_buffer.get_frame_inputs(
                frame=frame
            ):
                if input == InputBuffer.Value.LEFT:
                    player_one_state_data.player_node.add_to_position(Vector2.LEFT())
                    player_one_state_data.player_node.play(animation_name="Walk")
                    player_one_state_data.player_node.flip_h = True
                elif input == InputBuffer.Value.RIGHT:
                    player_one_state_data.player_node.add_to_position(Vector2.RIGHT())
                    player_one_state_data.player_node.play(animation_name="Walk")
                    player_one_state_data.player_node.flip_h = False

    def roll_back(self, frame: int, new_state) -> None:
        pass
