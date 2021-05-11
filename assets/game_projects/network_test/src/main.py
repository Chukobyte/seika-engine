from roll.node import Node
from roll.input import Input
from roll.engine import Engine
from roll.network import Server
from roll.network import Network


class Main(Node):
    def _start(self) -> None:
        print("Made it to main!")
        self.create_signal(signal_id="hello_signal")
        self.connect_signal(signal_id="hello_signal", listener_node=self, function_name="_on_Main_hello_signal")
        Network.connect_signal(signal_id="network_peer_connected", listener_node=self, function_name="_on_Network_network_peer_connected")
        Server.start(port=55555)

    def _physics_process(self, delta_time: float) -> None:
        if Input.is_action_just_pressed(action_name="quit"):
            Engine.exit()

        if Input.is_action_just_pressed(action_name="down"):
            self.emit_signal(signal_id="hello_signal", args=["my_arg"])

    def _on_Main_hello_signal(self, args: list) -> None:
        print(f"hello signal! args = {args}")

    def _on_Network_network_peer_connected(self, args: list) -> None:
        print("New connection established!")
