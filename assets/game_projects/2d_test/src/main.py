from seika.node import Node2D, Timer
from seika.input import Input
from seika.engine import Engine
from seika.physics import Collision


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

    def _physics_process(self, delta_time: float) -> None:
        if Input.is_action_just_pressed(action_name="quit"):
            Engine.exit()

        if Input.is_action_just_pressed(action_name="mouse_left_click"):
            print(f"collided_node_with_mouse = {Collision.get_nodes_under_mouse()}")

    def _on_timer_timeout(self, args: list) -> None:
        self.timeout_count += 1
        print(f"Timer timeout count = {self.timeout_count}!")
        if self.timeout_count >= 5:
            self.timer.queue_deletion()
            self.timer = None
