from roll.node import Node2D


class Test(Node2D):
    def _start(self) -> None:
        print("Start called!")

    def _physics_process(self, delta_time: float) -> None:
        print("Process!")
