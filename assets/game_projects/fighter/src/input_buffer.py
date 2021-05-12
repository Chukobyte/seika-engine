from roll.input import Input


class InputBuffer:
    """
    Responsible for collecting game input from both players.  The game state will pull data from here if needed.
    Network messages will also update the input buffer when receiving data from the opposite player
    """

    class Value:
        LEFT = "l"
        RIGHT = "r"
        UP = "u"
        DOWN = "d"

    def __init__(self):
        self._inputs = []

    def add_input(self, input: str) -> None:
        self._inputs.append(input)

    def get_inputs(self) -> list:
        return self._inputs

    def is_empty(self) -> bool:
        return len(self._inputs) == 0

    def clear(self):
        self._inputs.clear()

    def poll_client_inputs(self) -> None:
        if Input.is_action_pressed(action_name="left"):
            self.add_input(input=InputBuffer.Value.LEFT)
        elif Input.is_action_pressed(action_name="right"):
            self.add_input(input=InputBuffer.Value.RIGHT)
