import roll_engine_api

from roll.node import CollisionShape2D


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
