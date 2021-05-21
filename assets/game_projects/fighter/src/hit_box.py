import roll_engine_api

from roll.node import CollisionShape2D
from roll.physics import Collision


class HitBox(CollisionShape2D):
    # TODO: Investigate way to make child not have to implement
    @classmethod
    def new(cls):
        return roll_engine_api.node_new(
            class_path=f"{__name__}",
            class_name=f"{cls.__name__}",
            node_type=f"{cls.extract_valid_inheritance_node()}",
        )

    def _start(self) -> None:
        pass


class Attack(HitBox):
    def _start(self) -> None:
        self.frame_life_time = 0
        self.has_hit = False

    def has_collided_with_anything(self) -> bool:
        return len(Collision.get_collided_nodes(node=self)) > 0

    def get_collided_nodes(self) -> list:
        return Collision.get_collided_nodes(node=self)
