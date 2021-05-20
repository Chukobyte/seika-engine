from assets.game_projects.fighter.src.model.player import Player
from assets.game_projects.fighter.src.state.game_state_manager import (
    GameStateManager,
)
from assets.game_projects.fighter.src.state.state_data import (
    FrameStateData,
    FighterFrameStateData,
)


class StateSerializer:
    @staticmethod
    def serialize_frame(
        frame: int, game_state_manager: GameStateManager
    ) -> FrameStateData:
        player_one_state = game_state_manager.game_state.player_states[Player.ONE]
        player_one_frame_state_data = FighterFrameStateData()
        player_one_frame_state_data.player = player_one_state.id
        player_one_frame_state_data.position = player_one_state.node.position
        player_one_frame_state_data.inputs = (
            player_one_state.input_buffer.get_frame_inputs(frame=frame)
        )
        player_one_frame_state_data.animation.frame = player_one_state.node.frame
        player_one_frame_state_data.animation.animation_name = "idle"

        player_two_state = game_state_manager.game_state.player_states[Player.TWO]
        player_two_frame_state_data = FighterFrameStateData()
        player_two_frame_state_data.player = player_two_state.id
        player_two_frame_state_data.position = player_two_state.node.position
        player_two_frame_state_data.inputs = []
        if player_two_state and player_two_state.input_buffer:
            player_two_frame_state_data.inputs = (
                player_two_state.input_buffer.get_frame_inputs(frame=frame)
            )
        player_two_frame_state_data.animation.frame = player_two_state.node.frame
        player_two_frame_state_data.animation.animation_name = "idle"

        return FrameStateData(
            frame=frame,
            fighter_one_frame_data=player_one_frame_state_data,
            fighter_two_frame_data=player_two_frame_state_data,
        )
