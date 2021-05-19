import json

from roll.math import Vector2

# Roughing out player state data

# These will be stored by frame
class AnimationState:
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


class FighterFrameState:
    def __init__(self):
        self.player = 1
        self.position = Vector2(0.0, 0.0)
        self.inputs = ["l", "wp"]
        self.animation = AnimationState()
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
        return json.dumps(self.data, indent=4)

    def __repr__(self):
        return json.dumps(self.data, indent=4)
