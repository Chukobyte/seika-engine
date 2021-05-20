import json

from roll.math import Vector2

# These will be stored by frame
class AnimationStateData:
    def __init__(self):
        self.animation_name = "idle"
        self.frame = 0

    @property
    def data(self) -> dict:
        return {"animation_name": self.animation_name, "frame": self.frame}

    def __str__(self):
        return json.dumps(self.data)

    def __repr__(self):
        return json.dumps(self.data)


class FighterFrameStateData:
    def __init__(self):
        self.player = 1
        self.position = Vector2(0.0, 0.0)
        self.inputs = []
        self.animation = AnimationStateData()
        self.state = "idle"

    @property
    def data(self) -> dict:
        return {
            "player": self.player,
            "position": {"x": self.position.x, "y": self.position.y},
            "inputs": self.inputs,
            "animation": self.animation.data,
            "state": self.state,
        }

    def __str__(self):
        return json.dumps(self.data)

    def __repr__(self):
        return json.dumps(self.data)


class FrameStateData:
    def __init__(
        self,
        frame: int,
        fighter_one_frame_data: FighterFrameStateData,
        fighter_two_frame_data: FighterFrameStateData,
    ):
        self.frame = frame
        self.fighter_one_frame_data = fighter_one_frame_data
        self.fighter_two_frame_data = fighter_two_frame_data

    @property
    def data(self) -> dict:
        return {
            "frame": self.frame,
            "fighter_one": self.fighter_one_frame_data.data,
            "fighter_two": self.fighter_two_frame_data.data,
        }

    def __str__(self):
        return json.dumps(self.data)

    def __repr__(self):
        return json.dumps(self.data)
