from seika.assets import Font, Texture
from seika.color import Color
from seika.node import Node2D, Timer, TextLabel
from seika.input import Input
from seika.engine import Engine
from seika.physics import Collision
from seika.math import Vector2, Rect2
from seika.data import ConfigTool
from seika.audio import Audio


class Main(Node2D):
    def _start(self) -> None:
        print("2D test start!")
        self.timer = Timer.new()
        self.timer.wait_time = 2.0
        self.timer.loops = True
        self.timer.connect_signal("timeout", self, "_on_timer_timeout")
        self.add_child(child_node=self.timer)
        self.timer.start()
        self.timeout_count = 0

        self.seika_collision_shape = self.get_node(name="CollisionShape2D")

        # TODO: texture test
        idle_texture = Texture.get(file_path="assets/images/seika_idle.png")
        print(f"idle_texture = {idle_texture}")
        pixel_color = idle_texture.get_pixel_color(position=Vector2(24, 24))
        print(f"pixel_color = {pixel_color.get_full_color()}")

        # font = Font.create(uid="verdana-32", file_path="assets/fonts/verdana.ttf", size=32)
        # bruh_font = Font.get(uid="seika_default")
        # print(f"bruh font = {bruh_font}")
        #
        text_label = TextLabel.new()
        text_label.text = "Test Yeah!"
        text_label.position = Vector2(200, 100)
        # text_label.position = Vector2(10, 100)
        text_label.color = Color(1.0, 0.0, 0.0)
        self.add_child(child_node=text_label)
        # text_label.font = font
        # print(f"text_label.font = {text_label.font}")
        # config_tool = ConfigTool(file_path="game.sav", initial_data={"test": True})
        # config_tool.save_file()
        # config_tool = ConfigTool(file_path="game.sav")
        # config_tool.load_file()
        # print(config_tool.data)

        Audio.play_music(music_id="assets/audio/music/test_music.wav")

    def _physics_process(self, delta_time: float) -> None:
        if Input.is_action_just_pressed(action_name="quit"):
            Engine.exit()

        if Input.is_action_just_pressed(action_name="mouse_left_click"):
            # seika_node = self.get_node(name="Seika")
            # print(f"seika_node.texture = {seika_node.texture}")
            print(f"collided_node_with_mouse = {self.seika_collision_shape.is_under_mouse}")
            Audio.play_sound(sound_id="assets/audio/sound/test_sound_effect.wav")

    def _on_timer_timeout(self, args: list) -> None:
        self.timeout_count += 1
        print(f"Timer timeout count = {self.timeout_count}!")
        if self.timeout_count >= 5:
            self.timer.queue_deletion()
            self.timer = None
