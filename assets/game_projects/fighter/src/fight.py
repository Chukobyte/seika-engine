import json
import random

from roll.camera import Camera
from roll.input import Input
from roll.math import Vector2
from roll.network import Server, Network, Client
from roll.node import Node2D
from roll.scene import SceneTree

from assets.game_projects.fighter.src.network_message import (
    NetworkMessage,
    NetworkMessageKey,
)
from assets.game_projects.fighter.src.fight_simulator import FightSimulator
from assets.game_projects.fighter.src.game_properties import (
    GameProperties,
    PropertyValue,
)
from assets.game_projects.fighter.src.state.game_state_manager import GameStateManager
from assets.game_projects.fighter.src.state.game_state_serializer import StateSerializer


class Fight(Node2D):
    def _start(self) -> None:
        self.fight_simulator = FightSimulator()
        self.game_properties = GameProperties()
        self.frame_counter = 0
        self.game_state_manager = GameStateManager()

        self._process_game_start_mode()

    def _process_game_start_mode(self) -> None:
        self.game_state_manager.process_game_start_mode(
            game_start_mode=self.game_properties.player_opponent_mode, main=self
        )
        if (
            self.game_properties.player_opponent_mode
            == PropertyValue.PLAYER_OPPONENT_MODE_HOST_PLAYER_VS_PLAYER
        ):
            self._setup_server()
        elif (
            self.game_properties.player_opponent_mode
            == PropertyValue.PLAYER_OPPONENT_MODE_CLIENT_PLAYER_VS_PLAYER
        ):
            self._setup_client()

    def _process_inputs(self) -> None:
        # Temporary inputs for testing
        if Input.is_action_just_pressed(action_name="quit"):
            # Go back to main menu
            if (
                self.game_properties.player_opponent_mode
                == PropertyValue.PLAYER_OPPONENT_MODE_HOST_PLAYER_VS_PLAYER
            ):
                Server.stop()
            elif (
                self.game_properties.player_opponent_mode
                == PropertyValue.PLAYER_OPPONENT_MODE_CLIENT_PLAYER_VS_PLAYER
            ):
                Client.disconnect()
            SceneTree.change_scene(
                scene_path="assets/game_projects/fighter/scenes/title_screen.json"
            )
            # Engine.exit()

        if Input.is_action_just_pressed(action_name="zoom_in"):
            camera_zoom = Camera.get_zoom()
            camera_zoom -= Vector2(-0.1, -0.1)
            Camera.set_zoom(zoom=camera_zoom)

        if Input.is_action_just_pressed(action_name="zoom_out"):
            camera_zoom = Camera.get_zoom()
            camera_zoom -= Vector2(0.1, 0.1)
            Camera.set_zoom(zoom=camera_zoom)

        if Input.is_action_pressed(action_name="camera_left"):
            camera_position = Camera.get_viewport_position()
            camera_position += Vector2.LEFT()
            Camera.set_viewport_position(position=camera_position)
        elif Input.is_action_pressed(action_name="camera_right"):
            camera_position = Camera.get_viewport_position()
            camera_position += Vector2.RIGHT()
            Camera.set_viewport_position(position=camera_position)
        if Input.is_action_pressed(action_name="camera_up"):
            camera_position = Camera.get_viewport_position()
            camera_position += Vector2.UP()
            Camera.set_viewport_position(position=camera_position)
        elif Input.is_action_pressed(action_name="camera_down"):
            camera_position = Camera.get_viewport_position()
            camera_position += Vector2.DOWN()
            Camera.set_viewport_position(position=camera_position)

        if Input.is_action_pressed(action_name="camera_shake"):
            x_intensity_max = 5.0
            y_intensity_max = 5.0
            Camera.set_offset(
                Vector2(
                    random.uniform(-x_intensity_max, x_intensity_max),
                    random.uniform(-y_intensity_max, y_intensity_max),
                )
            )
        else:
            Camera.set_offset(offset=Vector2(0, 0))

        self.game_state_manager.game_state.poll_input(frame=self.frame_counter)

    # TODO: Decouple game state manager and make more procedural
    def _process_simulation(self) -> None:
        self.fight_simulator.simulate_frame(
            frame=self.frame_counter,
            game_state_manager=self.game_state_manager,
        )

    def _process_frame_serialization(self) -> None:
        frame_state_data = StateSerializer.serialize_frame(
            frame=self.frame_counter,
            game_state_manager=self.game_state_manager,
        )
        self.game_state_manager.game_state.save_frame_state(
            frame_state_data=frame_state_data
        )

    def _physics_process(self, delta_time: float) -> None:
        self._process_inputs()

        self._process_simulation()

        self._process_frame_serialization()

        self.game_properties.has_received_network_inputs = False

        self.frame_counter += 1

    # NETWORK

    def _setup_server(self) -> None:
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

    def _setup_client(self) -> None:
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
