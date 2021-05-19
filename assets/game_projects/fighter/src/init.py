from roll.node import Node2D
from roll.scene import SceneTree


class Init(Node2D):
    def _start(self) -> None:
        SceneTree.change_scene(
            scene_path="assets/game_projects/fighter/scenes/title_screen.json"
        )
        # player_state = PlayerState()
        # print(player_state)
