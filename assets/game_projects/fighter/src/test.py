import roll_engine_api
from roll.node import Node2D


class Test(Node2D):
    @classmethod
    def new(cls):
        return roll_engine_api.node_new(
            class_path="assets.game_projects.fighter.src.test",
            class_name="Test",
            node_type="Node2D",
        )

    def _start(self) -> None:
        print("Start called!")

    def _physics_process(self, delta_time: float) -> None:
        print("Process!")
