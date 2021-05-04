from roll.node import Node

class TestNode(Node):
    def _start(self) -> None:
        assert(self.entity_id == 1)

    def _physics_process(self, delta_time: float) -> None:
        pass

    def _end(self) -> None:
        pass
