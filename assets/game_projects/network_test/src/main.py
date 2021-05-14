import json
import time

from roll.node import Node2D
from roll.math import Vector2
from roll.input import Input
from roll.engine import Engine
from roll.network import Server, Client, Network

IS_SERVER = True
PORT = 6510
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


def truncate_float(f: float, n: int):
    """Truncates/pads a float f to n decimal places without rounding"""
    s = "{}".format(f)
    if "e" in s or "E" in s:
        return "{0:.{1}f}".format(f, n)
    i, p, d = s.partition(".")
    return ".".join([i, (d + "0" * n)[:n]])


class Main(Node2D):
    def _start(self) -> None:
        self.last_ping_time = None
        self.ping_timer = 0
        self.server_ping = 0.0
        self._setup_connections()
        if IS_SERVER:
            Server.start(port=PORT)
        else:
            Client.connect(endpoint=HOST_ENDPOINT, port=PORT)

    def _setup_connections(self) -> None:
        Network.connect_signal(
            signal_id="peer_connected",
            listener_node=self,
            function_name="_on_Network_peer_connected",
        )
        Network.connect_signal(
            signal_id="peer_disconnected",
            listener_node=self,
            function_name="_on_Network_peer_disconnected",
        )
        Network.connect_signal(
            signal_id="message_received",
            listener_node=self,
            function_name="_on_Network_message_received",
        )
        if not IS_SERVER:
            Network.connect_signal(
                signal_id="connected_to_server",
                listener_node=self,
                function_name="_on_Network_connected_to_server",
            )
            Network.connect_signal(
                signal_id="connection_to_server_failed",
                listener_node=self,
                function_name="_on_Network_connection_to_server_failed",
            )

    def _physics_process(self, delta_time: float) -> None:
        if Input.is_action_just_pressed(action_name="quit"):
            Engine.exit()

        input_buffer = self._process_inputs()
        if not input_buffer.is_empty():
            if IS_SERVER:
                Server.send_message_to_all_clients(
                    message=f"input = {input_buffer.inputs}, position = {self.position}"
                )
            else:
                Client.send_message_to_server(
                    message=f"input = {input_buffer.inputs}, position = {self.position}"
                )

        # Client sends ping
        if not IS_SERVER:
            if self.ping_timer >= 200:
                self.last_ping_time = time.time()
                self.ping_timer = 0
                message = {"id": "ping", "t": self.server_ping}
                Client.send_message_to_server(message=json.dumps(message))
            else:
                self.ping_timer += 1

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
            message = {"id": "text", "v": "Welcome to server!"}
            Server.send_message_to_all_clients(message=json.dumps(message))

    def _on_Network_peer_disconnected(self, args: list) -> None:
        print("A connection was disconnected!")

    def _on_Network_message_received(self, args: list) -> None:
        # Discards non json messages for now
        try:
            message_json = json.loads(args[0])
            message_id = message_json["id"]
            if message_id == "text":
                text = message_json["v"]
                print(f"Message from network '{text}'")
            elif message_id == "move":
                direction = message_json["dir"]
                position_x = message_json["px"]
                position_y = message_json["py"]
            elif message_id == "ping":
                if IS_SERVER:
                    client_ping = message_json["t"]
                    print(f"ping = {client_ping}")
                    message = {"id": "ping", "t": 0.0}
                    Server.send_message_to_all_clients(message=json.dumps(message))
                else:
                    current_time = time.time()
                    self.server_ping = truncate_float(
                        current_time - self.last_ping_time, 4
                    )
                    print(f"ping = {self.server_ping}")
                    self.last_ping_time = current_time
        except ValueError:
            print("Not valid json, skipping message")
        except Exception as e:
            print(f"Some other error: {e}")

    def _on_Network_connected_to_server(self, args: list) -> None:
        print("Connected to server!")
        message = {"id": "ping", "t": self.server_ping}
        self.last_ping_time = time.time()
        Client.send_message_to_server(message=json.dumps(message))

    def _on_Network_connection_to_server_failed(self, args: list) -> None:
        print("Connection to server failed!")
