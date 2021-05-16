import roll_engine_api
from roll.math import Rect2
from roll.node import CollisionShape2D


class Test(CollisionShape2D):
    @classmethod
    def new(cls):
        return roll_engine_api.node_new(
            class_path="assets.game_projects.fighter.src.test",
            class_name="Test",
            node_type="CollisionShape2D",
        )

    def _start(self) -> None:
        # print(f"Start called! Rect = {self.collider_rect}")
        # self.collider_rect = Rect2(x=300, y=300, w=40, h=40)
        pass

    def _physics_process(self, delta_time: float) -> None:
        # print("Process!")
        pass
