from seika.node import Spatial
from seika.input import Input, Mouse
from seika.engine import Engine
from seika.camera import Camera3D


class Main(Spatial):
    def _start(self) -> None:
        # print(f"position = {self.position}")
        self.pitch_yaw_sensitivity = 0.5
        # hide test
        # for i in range(10):
        #     wooden_container = self.get_node(name=f"WoodenContainer{i}")
        #     wooden_container.hide()
        print("3D test start!")

    def _physics_process(self, delta_time: float) -> None:
        if Input.is_action_just_pressed(action_name="quit"):
            Engine.exit()

        self._process_inputs(delta_time=delta_time)

        mouse_position = Mouse.get_position()
        print(f"mouse_position = {mouse_position}")

    def _process_inputs(self, delta_time: float) -> None:
        camera_move_speed = 10 * delta_time
        if Input.is_action_pressed(action_name="a_left_left"):
            Camera3D.move_left(speed=camera_move_speed)

        if Input.is_action_pressed(action_name="a_left_right"):
            Camera3D.move_right(speed=camera_move_speed)

        if Input.is_action_pressed(action_name="a_left_up"):
            Camera3D.move_up(speed=camera_move_speed)

        if Input.is_action_pressed(action_name="a_left_down"):
            Camera3D.move_down(speed=camera_move_speed)

        if Input.is_action_pressed(action_name="a_right_left"):
            Camera3D.add_yaw(yaw=-self.pitch_yaw_sensitivity)

        if Input.is_action_pressed(action_name="a_right_right"):
            Camera3D.add_yaw(yaw=self.pitch_yaw_sensitivity)

        if Input.is_action_pressed(action_name="a_right_up"):
            Camera3D.add_pitch(pitch=self.pitch_yaw_sensitivity)

        if Input.is_action_pressed(action_name="a_right_down"):
            Camera3D.add_pitch(pitch=-self.pitch_yaw_sensitivity)
