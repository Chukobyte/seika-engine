from roll.node import Node2D

class Test(Node2D):
    def _start(self) -> None:
        print(f"Hello World from entity with entity_id = {self.entity_id}!")

    def _physics_process(self, delta_time: float) -> None:
        pass

    def _end(self) -> None:
        pass
