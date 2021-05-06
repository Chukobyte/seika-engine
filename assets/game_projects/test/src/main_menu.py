from roll.node import Node
from roll.scene import SceneTree
from roll.input import Input
from roll.audio import Audio

class MainMenu(Node):
    def _start(self) -> None:
        Audio.play_music(music_id="assets/audio/music/test_music.wav")

    def _physics_process(self, delta_time: float) -> None:
        if Input.is_action_just_pressed(action_name="confirm"):
            SceneTree.change_scene(scene_path="assets/game_projects/test/scenes/test2.json")
            Audio.stop_music()
