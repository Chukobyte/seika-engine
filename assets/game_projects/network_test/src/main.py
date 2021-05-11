from roll.node import Node2D
from roll.math import Vector2
from roll.input import Input
from roll.engine import Engine
from roll.network import Server, Client, Network

IS_SERVER = True
PORT = 55555
HOST_ENDPOINT = "127.0.0.1"

class InputBuffer:
    class Value:
        LEFT = "l"
        RIGHT = "r"
        UP = "u"
        DOWN = "d"

    def __init__(self):
        self.inputs = []

    def add_input(self, input: str) -> None:
        self.inputs.append(input)

    def is_empty(self) -> bool:
        return len(self.inputs) == 0

class Main(Node2D):
    def _start(self) -> None:
        self._setup_connections()
        if IS_SERVER:
            Server.start(port=PORT)
        else:
            Client.connect(endpoint=HOST_ENDPOINT, port=PORT)

    def _setup_connections(self) -> None:
        Network.connect_signal(signal_id="peer_connected", listener_node=self, function_name="_on_Network_peer_connected")
        Network.connect_signal(signal_id="peer_disconnected", listener_node=self, function_name="_on_Network_peer_disconnected")
        Network.connect_signal(signal_id="message_received", listener_node=self, function_name="_on_Network_message_received")
        if not IS_SERVER:
            Network.connect_signal(signal_id="connected_to_server", listener_node=self, function_name="_on_Network_connected_to_server")
            Network.connect_signal(signal_id="connection_to_server_failed", listener_node=self, function_name="_on_Network_connection_to_server_failed")

    def _physics_process(self, delta_time: float) -> None:
        if Input.is_action_just_pressed(action_name="quit"):
            Engine.exit()

        input_buffer = self._process_inputs()
        if not input_buffer.is_empty():
            if IS_SERVER:
                Server.send_message_to_all_clients(message=f"input = {input_buffer.inputs}, position = {self.position}")
            else:
                Client.send_message_to_server(message=f"input = {input_buffer.inputs}, position = {self.position}")


    def _process_inputs(self) -> InputBuffer:
        input_buffer = InputBuffer()
        if Input.is_action_just_pressed(action_name="left"):
            input_buffer.add_input(input=InputBuffer.Value.LEFT)
            self.add_to_position(Vector2.LEFT())
        elif Input.is_action_just_pressed(action_name="right"):
            input_buffer.add_input(input=InputBuffer.Value.RIGHT)
            self.add_to_position(Vector2.RIGHT())
        if Input.is_action_just_pressed(action_name="up"):
            input_buffer.add_input(input=InputBuffer.Value.UP)
            self.add_to_position(Vector2.UP())
        elif Input.is_action_just_pressed(action_name="down"):
            input_buffer.add_input(input=InputBuffer.Value.DOWN)
            self.add_to_position(Vector2.DOWN())
        return input_buffer

    def _on_Network_peer_connected(self, args: list) -> None:
        print("New connection established!")
        if Network.is_server():
            Server.send_message_to_all_clients(message="Welcome to the server!")

    def _on_Network_peer_disconnected(self, args: list) -> None:
        print("A connection was disconnected!")

    def _on_Network_message_received(self, args: list) -> None:
        print(f"Message received from network = {args[0]}")

    def _on_Network_connected_to_server(self, args: list) -> None:
        print("Connected to server!")
        Client.send_message_to_server(message="A message from the client!")

    def _on_Network_connection_to_server_failed(self, args: list) -> None:
        print("Connection to server failed!")
