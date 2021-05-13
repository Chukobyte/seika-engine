from roll.node import Node2D
from roll.scene import SceneTree
from roll.input import Input
from roll.engine import Engine


class TitleScreen(Node2D):
    def _start(self) -> None:
        pass

    def _physics_process(self, delta_time: float) -> None:
        if Input.is_action_just_pressed(action_name="quit"):
            Engine.exit()

        if Input.is_action_just_pressed(action_name="confirm"):
            SceneTree.change_scene(
                scene_path="assets/game_projects/fighter/scenes/main.json"
            )
