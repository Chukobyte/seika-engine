from roll.engine import Engine
from roll.node import Node2D
from roll.math import Vector2
from roll.input import Input
from roll.camera import Camera
from roll.physics import Collision

class Puncher(Node2D):
    def _start(self) -> None:
        self.viewport = Vector2(1, 1)
        self.zoom = Vector2(1, 1)

    def _physics_process(self, delta_time: float) -> None:
        if Input.is_action_just_pressed(action_name="quit"):
            Engine.exit()

        if Input.is_action_pressed("zoom_out"):
            self.zoom += Vector2(0.1, 0.1)
            self.zoom = max(Vector2(0.1, 0.1), self.zoom)
            Camera.set_zoom(zoom=self.zoom)
        elif Input.is_action_pressed("zoom_in"):
            self.zoom += Vector2(-0.1, -0.1)
            self.zoom = min(Vector2(10, 10), self.zoom)
            Camera.set_zoom(zoom=self.zoom)

        if Input.is_action_pressed(action_name="up"):
            self.viewport.y -= 1
            Camera.set_viewport_position(position=self.viewport)
        elif Input.is_action_pressed(action_name="down"):
            self.viewport.y += 1
            Camera.set_viewport_position(position=self.viewport)
        if Input.is_action_pressed(action_name="left"):
            self.viewport.x -= 1
            Camera.set_viewport_position(position=self.viewport)
        elif Input.is_action_pressed(action_name="right"):
            self.viewport.x += 1
            Camera.set_viewport_position(position=self.viewport)

        if Collision.check(node=self):
            print("Has collided!")

    def _end(self) -> None:
        pass
