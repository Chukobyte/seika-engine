from roll.node import Node2D
from roll.math import Vector2

class Test(Node2D):
    def _start(self) -> None:
        self.start_position = self.get_position()

    def _physics_process(self, delta_time: float) -> None:
        self.add_to_position(Vector2(2.0, 0))
        if self.position.x > 800:
            self.position = Vector2(0, self.start_position.y)

    def _end(self) -> None:
        pass
