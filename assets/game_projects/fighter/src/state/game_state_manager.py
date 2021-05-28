from seika.node import Node

from assets.game_projects.fighter.src.game_properties import PropertyValue
from assets.game_projects.fighter.src.input_buffer import (
    InputBuffer,
    OutgoingNetworkInputBuffer,
    IncomingNetworkInputBuffer,
    AIInputBuffer,
)
from assets.game_projects.fighter.src.model.player import Player
from assets.game_projects.fighter.src.state.game_state import (
    GameState,
    UIState,
    PlayerState,
    AnimationState,
)


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
                up_action_name="one_up",
                down_action_name="one_down",
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
                up_action_name="one_up",
                down_action_name="one_down",
                weak_punch_action_name="one_weak_punch",
            )
            player_one_state.animation_state = AnimationState(
                node=player_one_state.node
            )

            player_two_state.node = main.get_node(name="PlayerTwo")
            player_two_state.input_buffer = InputBuffer(
                left_action_name="two_left",
                right_action_name="two_right",
                up_action_name="one_up",
                down_action_name="one_down",
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
                up_action_name="one_up",
                down_action_name="one_down",
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
                up_action_name="one_up",
                down_action_name="one_down",
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
