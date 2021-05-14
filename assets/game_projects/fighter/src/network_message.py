import json


class NetworkMessageKey:
    ID = "id"
    VALUE = "v"


class NetworkMessage:
    class ID:
        CONSOLE_MESSAGE = "cm"
        INPUTS = "in"

    def __init__(self, message_id: str, value):
        self._data = {
            NetworkMessageKey.ID: message_id,
            NetworkMessageKey.VALUE: value,
        }

    @property
    def id(self) -> str:
        return self._data[NetworkMessageKey.ID]

    @property
    def value(self):
        return self._data[NetworkMessageKey.VALUE]

    def __str__(self):
        return json.dumps(self._data)

    def __repr__(self):
        return json.dumps(self._data)


class ConsoleNetworkMessage(NetworkMessage):
    def __init__(self, value):
        super(ConsoleNetworkMessage, self).__init__(
            NetworkMessage.ID.CONSOLE_MESSAGE, value
        )
