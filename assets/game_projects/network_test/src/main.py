from roll.node import Node
from roll.input import Input
from roll.engine import Engine
from roll.network import Server, Client, Network

IS_SERVER = False
PORT = 55555
HOST_ENDPOINT = "127.0.0.1"

class Main(Node):
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
