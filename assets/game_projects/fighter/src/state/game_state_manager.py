from roll.node import TextLabel, Node, AnimatedSprite

from assets.game_projects.fighter.src.game_properties import PropertyValue
from assets.game_projects.fighter.src.input_buffer import (
    InputBuffer,
    OutgoingNetworkInputBuffer,
    IncomingNetworkInputBuffer,
    AIInputBuffer,
)
from assets.game_projects.fighter.src.state.state_data import (
    FighterFrameStateData,
    FrameStateData,
)


class Player:
    ONE = 1
    TWO = 2


class AnimationState:
    def __init__(self, node: AnimatedSprite):
        self.node = node
        self.current_frame = 0
        self.current_index = 0
        self.animation_name = ""
        self.frames_per_index = 0
        self.animation_frames = 0

    def set_animation(self, animation_name: str) -> None:
        if self.animation_name != animation_name:
            self.animation_name = animation_name
            self.node.set_animation(animation_name=animation_name)
            self.animation_frames = self.node.animation_frames
            self.frames_per_index = self.node.animation_speed / 10
            self.current_frame = 0
            self.current_index = 0

    def process_frame(self) -> None:
        self.node.frame = self.current_index
        if self.current_frame >= self.frames_per_index:
            self.current_index += 1
            if self.current_index >= self.animation_frames:
                self.current_index = 0
            self.current_frame = 0
        else:
            self.current_frame += 1


class PlayerState:
    def __init__(self, id: int):
        self.id = id
        self.node = None
        self.input_buffer = None
        self.animation_state = None


class GameState:
    def __init__(self):
        self.player_states = {
            Player.ONE: PlayerState(Player.ONE),
            Player.TWO: PlayerState(Player.TWO),
        }
        self.frame_states = {}

    def poll_input(self, frame: int) -> None:
        for player_number in self.player_states:
            player_state = self.player_states[player_number]
            if player_state and player_state.input_buffer:
                player_state.input_buffer.poll_client_inputs(frame=frame)

    def set_input_buffer(self, player: int, input_buffer: InputBuffer) -> None:
        self.player_states[player].input_buffer = input_buffer

    def set_player_state(self, player: int, state: PlayerState):
        self.player_states[player] = state

    def save_frame_state(self, frame_state_data: FrameStateData) -> None:
        self.frame_states[frame_state_data.frame] = frame_state_data


class UIState:
    def __init__(self):
        self.hp_labels = {
            Player.ONE: None,
            Player.TWO: None,
        }

    def set_hp_label(self, player: int, label: TextLabel) -> None:
        self.hp_labels[player] = label


class GameStateManager:
    __instance = None

    def __new__(cls, *args, **kwargs):
        if not GameStateManager.__instance:
            GameStateManager.__instance = object.__new__(cls)
            GameStateManager.reset()
        return GameStateManager.__instance

    @classmethod
    def reset(cls) -> None:
        cls.__instance._game_state = GameState()
        cls.__instance._ui_state = UIState()

    @property
    def game_state(self) -> GameState:
        return self._game_state

    @property
    def ui_state(self) -> UIState:
        return self._ui_state

    def process_game_start_mode(self, game_start_mode, main: Node) -> None:
        player_one_state = PlayerState(Player.ONE)
        player_two_state = PlayerState(Player.TWO)
        if game_start_mode == PropertyValue.PLAYER_OPPONENT_MODE_PLAYER_VS_COMPUTER:
            player_one_state.node = main.get_node(name="PlayerOne")
            player_one_state.input_buffer = InputBuffer(
                left_action_name="one_left",
                right_action_name="one_right",
                weak_punch_action_name="one_weak_punch",
            )
            player_one_state.animation_state = AnimationState(
                node=player_one_state.node
            )

            player_two_state.node = main.get_node(name="PlayerTwo")
            player_two_state.input_buffer = AIInputBuffer()
            player_two_state.animation_state = AnimationState(
                node=player_two_state.node
            )
        elif game_start_mode == PropertyValue.PLAYER_OPPONENT_MODE_PLAYER_VS_PLAYER:
            player_one_state.node = main.get_node(name="PlayerOne")
            player_one_state.input_buffer = InputBuffer(
                left_action_name="one_left",
                right_action_name="one_right",
                weak_punch_action_name="one_weak_punch",
            )
            player_one_state.animation_state = AnimationState(
                node=player_one_state.node
            )

            player_two_state.node = main.get_node(name="PlayerTwo")
            player_two_state.input_buffer = InputBuffer(
                left_action_name="two_left",
                right_action_name="two_right",
                weak_punch_action_name="two_weak_punch",
            )
            player_two_state.animation_state = AnimationState(
                node=player_two_state.node
            )
        elif (
            game_start_mode == PropertyValue.PLAYER_OPPONENT_MODE_HOST_PLAYER_VS_PLAYER
        ):
            player_one_state.node = main.get_node(name="PlayerOne")
            player_one_state.input_buffer = OutgoingNetworkInputBuffer(
                left_action_name="one_left",
                right_action_name="one_right",
                weak_punch_action_name="one_weak_punch",
            )
            player_one_state.animation_state = AnimationState(
                node=player_one_state.node
            )

            player_two_state.node = main.get_node(name="PlayerTwo")
            player_two_state.input_buffer = IncomingNetworkInputBuffer()
            player_two_state.animation_state = AnimationState(
                node=player_two_state.node
            )
        elif (
            game_start_mode
            == PropertyValue.PLAYER_OPPONENT_MODE_CLIENT_PLAYER_VS_PLAYER
        ):
            player_one_state.node = main.get_node(name="PlayerTwo")
            player_one_state.input_buffer = OutgoingNetworkInputBuffer(
                left_action_name="one_left",
                right_action_name="one_right",
                weak_punch_action_name="one_weak_punch",
            )
            player_one_state.animation_state = AnimationState(
                node=player_one_state.node
            )

            player_two_state.node = main.get_node(name="PlayerOne")
            player_two_state.input_buffer = IncomingNetworkInputBuffer()
            player_two_state.animation_state = AnimationState(
                node=player_two_state.node
            )

        self._game_state.set_player_state(player=Player.ONE, state=player_one_state)
        self._game_state.set_player_state(player=Player.TWO, state=player_two_state)

        self._ui_state.set_hp_label(
            player=Player.ONE, label=main.get_node(name="PlayerOneHealthText")
        )
        self._ui_state.set_hp_label(
            player=Player.TWO, label=main.get_node(name="PlayerTwoHealthText")
        )
