from roll.node import TextLabel, Node

from assets.game_projects.fighter.src.game_properties import PropertyValue
from assets.game_projects.fighter.src.input_buffer import (
    InputBuffer,
    OutgoingNetworkInputBuffer,
    IncomingNetworkInputBuffer,
)


class Player:
    ONE = 1
    TWO = 2


class PlayerState:
    def __init__(self):
        self.node = None
        self.input_buffer = None


class GameState:
    def __init__(self):
        self.player_states = {Player.ONE: PlayerState(), Player.TWO: PlayerState()}

    def poll_input(self, frame: int) -> None:
        for player_number in self.player_states:
            player_state = self.player_states[player_number]
            if player_state:
                player_state.input_buffer.poll_client_inputs(frame=frame)

    def set_input_buffer(self, player: int, input_buffer: InputBuffer) -> None:
        self.player_states[player].input_buffer = input_buffer

    def set_player_state(self, player: int, state: PlayerState):
        self.player_states[player] = state


class UIState:
    def __init__(self):
        self.hp_labels = {
            Player.ONE: None,
            Player.TWO: None,
        }

    def set_hp_label(self, player, label: TextLabel) -> None:
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
        cls.__instance.game_state = GameState()
        cls.__instance.ui_state = UIState()

    def process_game_start_mode(self, game_start_mode, main: Node) -> None:
        player_one_state = PlayerState()
        player_two_state = PlayerState()
        if game_start_mode == PropertyValue.PLAYER_OPPONENT_MODE_PLAYER_VS_COMPUTER:
            player_one_state.node = main.get_node(name="PlayerOne")
            player_one_state.input_buffer = InputBuffer(
                left_action_name="one_left",
                right_action_name="one_right",
                weak_punch_action_name="one_weak_punch",
            )

            player_two_state.node = main.get_node(name="PlayerTwo")
            player_two_state.input_buffer = None
        elif game_start_mode == PropertyValue.PLAYER_OPPONENT_MODE_PLAYER_VS_PLAYER:
            player_one_state.node = main.get_node(name="PlayerOne")
            player_one_state.input_buffer = InputBuffer(
                left_action_name="one_left",
                right_action_name="one_right",
                weak_punch_action_name="one_weak_punch",
            )

            player_two_state.node = main.get_node(name="PlayerTwo")
            player_two_state.input_buffer = InputBuffer(
                left_action_name="two_left",
                right_action_name="two_right",
                weak_punch_action_name="two_weak_punch",
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

            player_two_state.node = main.get_node(name="PlayerTwo")
            player_two_state.input_buffer = IncomingNetworkInputBuffer()
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

            player_two_state.node = main.get_node(name="PlayerOne")
            player_two_state.input_buffer = IncomingNetworkInputBuffer()

        self.game_state.set_player_state(player=Player.ONE, state=player_one_state)
        self.game_state.set_player_state(player=Player.TWO, state=player_two_state)
