from enum import auto
from assets.game_projects.fighter.src.auto_enum import AutoName


class PropertyName(AutoName):
    PLAYER_OPPONENT_MODE = auto()


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
                PropertyName.PLAYER_OPPONENT_MODE: PropertyValue.PLAYER_OPPONENT_MODE_PLAYER_VS_COMPUTER
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
