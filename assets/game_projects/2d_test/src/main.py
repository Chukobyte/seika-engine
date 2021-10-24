from seika.assets import Font, Texture
from seika.node import Node2D, Timer, TextLabel
from seika.input import Input
from seika.engine import Engine
from seika.physics import Collision
from seika.math import Vector2, Rect2
from seika.data import ConfigTool


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

        # font = Font.create(uid="verdana-32", file_path="assets/fonts/verdana.ttf", size=32)
        # bruh_font = Font.get(uid="seika_default")
        # print(f"bruh font = {bruh_font}")
        #
        # text_label = TextLabel.new()
        # text_label.text = "Test Yeah!"
        # text_label.position = Vector2(100, 100)
        # text_label.font = font
        # self.add_child(child_node=text_label)
        # print(f"text_label.font = {text_label.font}")
        # config_tool = ConfigTool(file_path="game.sav", initial_data={"test": True})
        # config_tool.save_file()
        # config_tool = ConfigTool(file_path="game.sav")
        # config_tool.load_file()
        # print(config_tool.data)


    def _physics_process(self, delta_time: float) -> None:
        if Input.is_action_just_pressed(action_name="quit"):
            Engine.exit()

        if Input.is_action_just_pressed(action_name="mouse_left_click"):
            # seika_node = self.get_node(name="Seika")
            # print(f"seika_node.texture = {seika_node.texture}")
            print(f"collided_node_with_mouse = {self.seika_collision_shape.is_under_mouse}")

    def _on_timer_timeout(self, args: list) -> None:
        self.timeout_count += 1
        print(f"Timer timeout count = {self.timeout_count}!")
        if self.timeout_count >= 5:
            self.timer.queue_deletion()
            self.timer = None
