from seika.node import Node
from seika.input import Input
from seika.engine import Engine
from seika.camera import Camera3D


class Main(Node):
    def _start(self) -> None:
        print("3D test start!")

    def _physics_process(self, delta_time: float) -> None:
        if Input.is_action_just_pressed(action_name="quit"):
            Engine.exit()

        self._process_inputs(delta_time=delta_time)

    def _process_inputs(self, delta_time: float) -> None:
        camera_move_speed = 50 * delta_time
        if Input.is_action_pressed(action_name="a_left_left"):
            Camera3D.move_left(speed=camera_move_speed)

        if Input.is_action_pressed(action_name="a_left_right"):
            Camera3D.move_right(speed=camera_move_speed)

        if Input.is_action_pressed(action_name="a_left_up"):
            Camera3D.move_up(speed=camera_move_speed)

        if Input.is_action_pressed(action_name="a_left_down"):
            Camera3D.move_down(speed=camera_move_speed)

        if Input.is_action_pressed(action_name="a_right_left"):
            print("Right Analog pressed left")

        if Input.is_action_pressed(action_name="a_right_right"):
            print("Right Analog pressed right")

        if Input.is_action_pressed(action_name="a_right_up"):
            print("Right Analog pressed up")

        if Input.is_action_pressed(action_name="a_right_down"):
            print("Right Analog pressed down")
