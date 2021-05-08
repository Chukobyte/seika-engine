from roll.engine import Engine
from roll.node import Node2D
from roll.math import Vector2
from roll.input import Input
from roll.camera import Camera
from roll.physics import Collision
from roll.scene import SceneTree

class Puncher(Node2D):
    def _start(self) -> None:
        self.viewport = Vector2(1, 1)
        self.zoom = Vector2(1, 1)

    def _physics_process(self, delta_time: float) -> None:
        if Input.is_action_just_pressed(action_name="quit"):
            # Engine.exit()
            # SceneTree.change_scene(scene_path="assets/game_projects/test/scenes/test_battle.json")

            # entity = SceneTree.get_current_scene_node()
            # print(f"SceneTree.get_current_scene_node() = {entity.entity_id}")
            # entity.position += Vector2(5.0, 5.0)
            # print(f"SceneTree.get_current_scene_node() = {entity.position}")

            collided_nodes = Collision.get_collided_nodes(self)
            print(f"collided_nodes = {collided_nodes}")
            # for collided_node in collided_nodes:
            #     print(f"collided_node = {collided_node}")

        self.camera_controls()
        self.movement_controls()

        # if Collision.check(node=self):
        #     print("Has collided!")

    def movement_controls(self) -> None:
        if Input.is_action_pressed(action_name="left"):
            self.add_to_position(value=Vector2(-1, 0))
        elif Input.is_action_pressed(action_name="right"):
            self.add_to_position(value=Vector2(1, 0))

    def camera_controls(self) -> None:
        if Input.is_action_pressed("zoom_out"):
            self.zoom += Vector2(0.1, 0.1)
            self.zoom = max(Vector2(0.1, 0.1), self.zoom)
            Camera.set_zoom(zoom=self.zoom)
        elif Input.is_action_pressed("zoom_in"):
            self.zoom += Vector2(-0.1, -0.1)
            self.zoom = min(Vector2(10, 10), self.zoom)
            Camera.set_zoom(zoom=self.zoom)

        if Input.is_action_pressed(action_name="camera_up"):
            self.viewport.y -= 1
            Camera.set_viewport_position(position=self.viewport)
        elif Input.is_action_pressed(action_name="camera_down"):
            self.viewport.y += 1
            Camera.set_viewport_position(position=self.viewport)
        if Input.is_action_pressed(action_name="camera_left"):
            self.viewport.x -= 1
            Camera.set_viewport_position(position=self.viewport)
        elif Input.is_action_pressed(action_name="camera_right"):
            self.viewport.x += 1
            Camera.set_viewport_position(position=self.viewport)

    def _end(self) -> None:
        pass
