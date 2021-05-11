from roll.node import Node
from roll.input import Input
from roll.engine import Engine
from roll.network import Server, Network


class Main(Node):
    def _start(self) -> None:
        Network.connect_signal(signal_id="peer_connected", listener_node=self, function_name="_on_Network_peer_connected")
        Network.connect_signal(signal_id="peer_disconnected", listener_node=self, function_name="_on_Network_peer_disconnected")
        Network.connect_signal(signal_id="message_received", listener_node=self, function_name="_on_Network_message_received")
        Server.start(port=55555)
        print(f"Is network a server = {Network.is_server()}")

    def _physics_process(self, delta_time: float) -> None:
        if Input.is_action_just_pressed(action_name="quit"):
            Engine.exit()

    def _on_Network_peer_connected(self, args: list) -> None:
        print("New connection established!")
        Server.send_message_to_all_clients(message="Welcome to the server!")

    def _on_Network_peer_disconnected(self, args: list) -> None:
        print("A connection was disconnected!")

    def _on_Network_message_received(self, args: list) -> None:
        print(f"Message received from client = {args[0]}")
