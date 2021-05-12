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

    def __init__(self, frame_limit=12):
        self._inputs = {}
        self._frame_limit = frame_limit

    def __str__(self):
        return f"{self._inputs}"

    def __repr__(self):
        return f"{self._inputs}"

    def add_input(self, input: str, frame: int) -> None:
        if frame in self._inputs:
            self._inputs[frame].append(input)
        else:
            self._inputs[frame] = [input]

    def get_inputs(self) -> dict:
        return self._inputs

    def get_frame_inputs(self, frame: int) -> list:
        return self._inputs.get(frame, [])

    def is_empty(self) -> bool:
        return len(self._inputs) == 0

    def clear(self):
        self._inputs.clear()

    def poll_client_inputs(self, frame: int) -> None:
        if Input.is_action_pressed(action_name="left"):
            self.add_input(input=InputBuffer.Value.LEFT, frame=frame)
        elif Input.is_action_pressed(action_name="right"):
            self.add_input(input=InputBuffer.Value.RIGHT, frame=frame)

        self._inputs.pop(frame - self._frame_limit, None)
