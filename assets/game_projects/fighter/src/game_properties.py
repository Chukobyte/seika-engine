class PropertyName:
    PLAYER_OPPONENT_MODE = "player_opponent_mode"


class PropertyValue:
    PLAYER_OPPONENT_MODE_PLAYER_VS_COMPUTER = "pvc"
    PLAYER_OPPONENT_MODE_PLAYER_VS_PLAYER = "pvp"
    PLAYER_OPPONENT_MODE_HOST_PLAYER_VS_PLAYER = "hpvp"
    PLAYER_OPPONENT_MODE_CLIENT_PLAYER_VS_PLAYER = "cpvp"


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
