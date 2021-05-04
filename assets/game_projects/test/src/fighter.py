from roll.engine import Engine
from roll.node import Node2D
from roll.math import Vector2
from roll.input import Input
from roll.audio import Audio

class Puncher(Node2D):
    def _start(self) -> None:
        Audio.play_music(music_id="assets/audio/music/test_music.wav")

    def _physics_process(self, delta_time: float) -> None:
        if Input.is_action_just_pressed(action_name="quit"):
            Engine.exit()

        if Input.is_action_just_pressed(action_name="up") or Input.is_action_just_pressed(action_name="down"):
            Audio.play_sound(sound_id="assets/audio/sound/test_sound_effect.wav")

        if Input.is_action_pressed(action_name="right"):
            self.add_to_position(Vector2(1.0, 0))
        elif Input.is_action_pressed(action_name="left"):
            self.add_to_position(Vector2(-1.0, 0))

    def _end(self) -> None:
        pass
