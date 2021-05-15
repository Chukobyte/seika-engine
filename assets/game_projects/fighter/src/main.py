import json

from roll.node import Node2D, AnimatedSprite
from roll.input import Input
from roll.engine import Engine
from roll.math import Vector2
from roll.network import Server, Client, Network

from assets.game_projects.fighter.src.fight_state import FightState, PlayerStateData
from assets.game_projects.fighter.src.input_buffer import (
    InputBuffer,
    OutgoingNetworkInputBuffer,
    IncomingNetworkInputBuffer,
)
from assets.game_projects.fighter.src.fight_simulator import FightSimulator
from assets.game_projects.fighter.src.game_properties import (
    GameProperties,
    PropertyValue,
)
from assets.game_projects.fighter.src.network_message import (
    NetworkMessageKey,
    NetworkMessage,
)


class Main(Node2D):
    def _start(self) -> None:
        self.fight_simulator = FightSimulator()
        self.game_properties = GameProperties()
        self.fight_state = FightState()
        self.frame_counter = 0
        self.input_buffers = []

        self._process_game_mode()

    def _process_game_mode(self) -> None:
        if (
            self.game_properties.player_opponent_mode
            == PropertyValue.PLAYER_OPPONENT_MODE_PLAYER_VS_COMPUTER
        ):
            self.player_one_state_data = PlayerStateData(
                player_node=self.get_node(name="PlayerOne"),
                player_input_buffer=InputBuffer(
                    left_action_name="one_left", right_action_name="one_right"
                ),
            )
            self.input_buffers.append(self.player_one_state_data.player_input_buffer)

            self.player_two_state_data = None
        elif (
            self.game_properties.player_opponent_mode
            == PropertyValue.PLAYER_OPPONENT_MODE_PLAYER_VS_PLAYER
        ):
            self.player_one_state_data = PlayerStateData(
                player_node=self.get_node(name="PlayerOne"),
                player_input_buffer=InputBuffer(
                    left_action_name="one_left", right_action_name="one_right"
                ),
            )
            self.input_buffers.append(self.player_one_state_data.player_input_buffer)

            self.player_two_state_data = PlayerStateData(
                player_node=self.get_node(name="PlayerTwo"),
                player_input_buffer=InputBuffer(
                    left_action_name="two_left", right_action_name="two_right"
                ),
            )
            self.input_buffers.append(self.player_two_state_data.player_input_buffer)
        elif (
            self.game_properties.player_opponent_mode
            == PropertyValue.PLAYER_OPPONENT_MODE_HOST_PLAYER_VS_PLAYER
        ):
            self.player_one_state_data = PlayerStateData(
                player_node=self.get_node(name="PlayerOne"),
                player_input_buffer=OutgoingNetworkInputBuffer(
                    left_action_name="one_left", right_action_name="one_right"
                ),
            )
            self.input_buffers.append(self.player_one_state_data.player_input_buffer)

            self.player_two_state_data = PlayerStateData(
                player_node=self.get_node(name="PlayerTwo"),
                player_input_buffer=IncomingNetworkInputBuffer(),
            )
            self.input_buffers.append(self.player_two_state_data.player_input_buffer)

            self.game_properties.is_server = True
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
            Server.start(port=self.game_properties.server_port)
            print("Server started...")
        elif (
            self.game_properties.player_opponent_mode
            == PropertyValue.PLAYER_OPPONENT_MODE_CLIENT_PLAYER_VS_PLAYER
        ):
            self.player_one_state_data = PlayerStateData(
                player_node=self.get_node(name="PlayerTwo"),
                player_input_buffer=OutgoingNetworkInputBuffer(
                    left_action_name="one_left", right_action_name="one_right"
                ),
            )
            self.input_buffers.append(self.player_one_state_data.player_input_buffer)

            self.player_two_state_data = PlayerStateData(
                player_node=self.get_node(name="PlayerOne"),
                player_input_buffer=IncomingNetworkInputBuffer(),
            )
            self.input_buffers.append(self.player_two_state_data.player_input_buffer)

            Network.connect_signal(
                signal_id="message_received",
                listener_node=self,
                function_name="_on_Network_message_received",
            )
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
            print("Client attempting to connect to server...")
            Client.connect(
                endpoint=self.game_properties.server_endpoint,
                port=self.game_properties.server_port,
            )

    def _physics_process(self, delta_time: float) -> None:
        self._process_inputs()

        self._process_simulation()

        self.fight_state.serialize(
            frame=self.frame_counter,
            player_one_state_data=self.player_one_state_data,
            player_two_state_data=self.player_two_state_data,
        )
        # print(f"fight_state = {self.fight_state}")

        self.game_properties.has_received_network_inputs = False
        self.frame_counter += 1

    def _process_inputs(self) -> None:
        if Input.is_action_just_pressed(action_name="quit"):
            Engine.exit()

        for input_buffer in self.input_buffers:
            input_buffer.poll_client_inputs(frame=self.frame_counter)

    def _process_simulation(self) -> None:
        self.fight_simulator.simulate_frame(
            frame=self.frame_counter,
            player_one_state_data=self.player_one_state_data,
            player_two_state_data=self.player_two_state_data,
        )

    # NETWORKING

    # Server
    def _on_Network_peer_connected(self, args: list) -> None:
        print("Client connected")
        Server.send_message_to_all_clients(
            message=f"{NetworkMessage(message_id=NetworkMessage.ID.CONSOLE_MESSAGE, value='Welcome to the server!')}"
        )

    def _on_Network_peer_disconnected(self, args: list) -> None:
        print("Client disconnected")

    # Client
    def _on_Network_connected_to_server(self, args: list) -> None:
        print("Connected to server!")
        Client.send_message_to_server(
            message=f"{NetworkMessage(message_id=NetworkMessage.ID.CONSOLE_MESSAGE, value='A message from the client')}"
        )

    def _on_Network_connection_to_server_failed(self, args: list) -> None:
        print("Connection to server failed!")

    # Both
    def _on_Network_message_received(self, args: list) -> None:
        try:
            message_json = json.loads(args[0])
            message_id = message_json[NetworkMessageKey.ID]
            message_value = message_json[NetworkMessageKey.VALUE]

            if message_id == NetworkMessage.ID.INPUTS:
                # print(f"received inputs = {message_value}")
                # TODO: update input buffer for other player
                for input in message_value:
                    self.player_two_state_data.player_input_buffer.add_input(
                        input=input, frame=self.frame_counter
                    )
                self.game_properties.has_received_network_inputs = True
            elif message_id == NetworkMessage.ID.CONSOLE_MESSAGE:
                print(f"network message = {message_value}")
        except ValueError:
            print(f"Not valid json, skipping message:\nMessage = {args[0]}")
            # pass
        except Exception as e:
            print(f"Some other error: {e}\nMessage = {args[0]}")
        if self.game_properties.is_server:
            pass
        else:
            pass
