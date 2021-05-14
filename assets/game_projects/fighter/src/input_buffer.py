from enum import Enum

from roll.input import Input
from roll.network import Server, Client

from assets.game_projects.fighter.src.game_properties import GameProperties
from assets.game_projects.fighter.src.network_message import NetworkMessage


class InputBuffer:
    """
    Responsible for collecting game input from both players.  The game state will pull data from here if needed.
    Network messages will also update the input buffer when receiving data from the opposite player
    """

    class Value(Enum):
        LEFT = "l"
        RIGHT = "r"
        UP = "u"
        DOWN = "d"

    def __init__(self, left_action_name: str, right_action_name: str, frame_limit=12):
        self._inputs = {}
        self.left_action_name = left_action_name
        self.right_action_name = right_action_name
        self._frame_limit = frame_limit

    def __str__(self):
        return f"{self._inputs}"

    def __repr__(self):
        return f"{self._inputs}"

    @property
    def values(self) -> list:
        return self._inputs.values()

    def add_input(self, input, frame: int) -> None:
        if frame in self._inputs:
            self._inputs[frame].append(input.value)
        else:
            self._inputs[frame] = [input.value]

    def get_inputs(self) -> dict:
        return self._inputs

    def get_frame_inputs(self, frame: int) -> list:
        return self._inputs.get(frame, [])

    def is_empty(self) -> bool:
        return len(self._inputs) == 0

    def clear(self):
        self._inputs.clear()

    def poll_client_inputs(self, frame: int) -> None:
        if Input.is_action_pressed(action_name=self.left_action_name):
            self.add_input(input=InputBuffer.Value.LEFT, frame=frame)
        elif Input.is_action_pressed(action_name=self.right_action_name):
            self.add_input(input=InputBuffer.Value.RIGHT, frame=frame)

        self._inputs.pop(frame - self._frame_limit, None)


class OutgoingNetworkInputBuffer(InputBuffer):
    def __init__(self, left_action_name: str, right_action_name: str, frame_limit=12):
        super().__init__(
            left_action_name=left_action_name,
            right_action_name=right_action_name,
            frame_limit=frame_limit,
        )
        self.game_properties = GameProperties()

    def poll_client_inputs(self, frame: int) -> None:
        super().poll_client_inputs(frame=frame)
        frame_inputs = self.get_frame_inputs(frame=frame)
        if frame_inputs:
            if self.game_properties.is_server:
                Server.send_message_to_all_clients(
                    message=f"{NetworkMessage(message_id=NetworkMessage.ID.INPUTS, value=frame_inputs)}"
                )
            else:
                Client.send_message_to_server(
                    message=f"{NetworkMessage(message_id=NetworkMessage.ID.INPUTS, value=frame_inputs)}"
                )


class IncomingNetworkInputBuffer(InputBuffer):
    def __init__(self, frame_limit=12):
        super().__init__(
            left_action_name="",
            right_action_name="",
            frame_limit=frame_limit,
        )
        self.game_properties = GameProperties()

    def add_input(self, input: str, frame: int) -> None:
        if frame in self._inputs:
            self._inputs[frame].append(input)
        else:
            self._inputs[frame] = [input]

    def poll_client_inputs(self, frame: int) -> None:
        self._inputs.pop(frame - self._frame_limit, None)
