from enum import auto
from assets.game_projects.fighter.src.auto_enum import AutoName


class PropertyName(AutoName):
    PLAYER_OPPONENT_MODE = auto()
    IS_SERVER = auto()
    SERVER_PORT = auto()
    SERVER_ENDPOINT = auto()
    HAS_RECEIVED_NETWORK_INPUTS = auto()


class PropertyValue(AutoName):
    PLAYER_OPPONENT_MODE_PLAYER_VS_COMPUTER = auto()
    PLAYER_OPPONENT_MODE_PLAYER_VS_PLAYER = auto()
    PLAYER_OPPONENT_MODE_HOST_PLAYER_VS_PLAYER = auto()
    PLAYER_OPPONENT_MODE_CLIENT_PLAYER_VS_PLAYER = auto()


class GameProperties:

    __instance = None

    def __new__(cls, *args, **kwargs):
        if not GameProperties.__instance:
            GameProperties.__instance = object.__new__(cls)
            GameProperties.__instance._data = {
                PropertyName.PLAYER_OPPONENT_MODE: PropertyValue.PLAYER_OPPONENT_MODE_PLAYER_VS_COMPUTER,
                PropertyName.IS_SERVER: False,
                PropertyName.SERVER_PORT: 6510,
                PropertyName.SERVER_ENDPOINT: "127.0.0.1",
                PropertyName.HAS_RECEIVED_NETWORK_INPUTS: False,
            }
        return GameProperties.__instance

    def __str__(self):
        return f"{self._data}"

    def __repr__(self):
        return f"{self._data}"

    @property
    def player_opponent_mode(self) -> str:
        return self._data[PropertyName.PLAYER_OPPONENT_MODE]

    @player_opponent_mode.setter
    def player_opponent_mode(self, value: str) -> None:
        self._data[PropertyName.PLAYER_OPPONENT_MODE] = value

    @property
    def is_server(self) -> bool:
        return self._data[PropertyName.IS_SERVER]

    @is_server.setter
    def is_server(self, value: bool) -> None:
        self._data[PropertyName.IS_SERVER] = value

    @property
    def server_port(self) -> int:
        return self._data[PropertyName.SERVER_PORT]

    @server_port.setter
    def server_port(self, value: int) -> None:
        self._data[PropertyName.SERVER_PORT] = value

    @property
    def server_endpoint(self) -> str:
        return self._data[PropertyName.SERVER_ENDPOINT]

    @server_endpoint.setter
    def server_endpoint(self, value: str) -> None:
        self._data[PropertyName.SERVER_ENDPOINT] = value

    @property
    def has_received_network_inputs(self) -> bool:
        return self._data[PropertyName.HAS_RECEIVED_NETWORK_INPUTS]

    @has_received_network_inputs.setter
    def has_received_network_inputs(self, value: bool) -> None:
        self._data[PropertyName.HAS_RECEIVED_NETWORK_INPUTS] = value
