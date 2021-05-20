from assets.game_projects.fighter.src.state.game_state_manager import (
    GameState,
    PlayerState,
)
from assets.game_projects.fighter.src.state.state_data import (
    FrameStateData,
    FighterFrameStateData,
)


class StateSerializer:
    @staticmethod
    def serialize_frame(
        self, frame: int, player_one_state: PlayerState, player_two_state: PlayerState
    ) -> FrameStateData:
        player_one_frame_state_data = FighterFrameStateData()
        player_one_frame_state_data.player = player_one_state.id
        player_one_frame_state_data.position = player_one_state.node.position
        player_one_frame_state_data.inputs = (
            player_one_state.input_buffer.get_frame_inputs(frame=frame)
        )
        player_one_frame_state_data.animation.frame = player_one_state.node.frame
        player_one_frame_state_data.animation.animation_name = "idle"

        player_two_frame_state_data = FighterFrameStateData()
        player_two_frame_state_data.player = player_two_state.id
        player_two_frame_state_data.position = player_two_state.node.position
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
