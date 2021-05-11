from roll.node import Node, Node2D
from roll.math import Vector2
from roll.physics import Collision
from roll.input import Input
from roll.network import Server, Client


class Player:
    ONE = 1
    TWO = 2


class PlayerState:
    def __init__(self, player: int, health=10, position=Vector2(0, 0)):
        self.player = player
        self.health = health
        self.position = position
        self.frames_invincible_after_damage = 0

    def __str__(self):
        data = {
            "player": self.player,
            "health": self.health,
            "position": self.position,
            "frames_invincible_after_damage": self.frames_invincible_after_damage,
        }
        return f"{data}"

    def __repr__(self):
        data = {
            "player": self.player,
            "health": self.health,
            "position": self.position,
            "frames_invincible_after_damage": self.frames_invincible_after_damage,
        }
        return f"{data}"


class FrameState:
    def __init__(
        self, frame, player_one_state: PlayerState, player_two_state: PlayerState
    ) -> None:
        self.frame = frame
        self.player_states = {
            Player.ONE: player_one_state,
            Player.TWO: player_two_state,
        }

    def __str__(self):
        data = {"frame": self.frame, "player_states": self.player_states}
        return f"{data}"

    def __repr__(self):
        data = {"frame": self.frame, "player_states": self.player_states}
        return f"{data}"


class PlayState:
    def __init__(self):
        self.player_one = PlayerState(player=Player.ONE)
        self.player_two = PlayerState(player=Player.TWO)
        self.current_frame = 0
        self.frames = {}
        self.frame_retention = 7

    def __str__(self):
        return f"{self.frames}"

    def __repr__(self):
        return f"{self.frames}"

    def save_state(self, player_one_node: Node2D, player_two_node: Node2D) -> None:
        self.player_one.position = player_one_node.position
        self.player_two.position = player_two_node.position
        self.frames[self.current_frame] = FrameState(
            frame=self.current_frame,
            player_one_state=self.player_one,
            player_two_state=self.player_two,
        )
        if self.current_frame - self.frame_retention in self.frames:
            del self.frames[self.current_frame - self.frame_retention]


class Battle(Node2D):
    def _start(self) -> None:
        self.play_state = PlayState()
        self.player_one = self.get_node(name="PlayerOne")
        self.player_two = self.get_node(name="PlayerTwo")

        self.player_one_health_text_label = self.get_node(name="PlayerOneHealthText")
        self.player_two_health_text_label = self.get_node(name="PlayerTwoHealthText")
        print("Battle created!")

        self._update_player_health_text(player=Player.ONE)
        self._update_player_health_text(player=Player.TWO)

        self.server_started = True
        Server.start(port=55555)
        # Client.connect(endpoint="127.0.0.1", port=55555)
        self.time = 0

    def _update_player_health_text(self, player: int) -> None:
        if player == Player.ONE:
            self.player_one_health_text_label.text = (
                f"Player {player}: {self.play_state.player_one.health} HP"
            )
        elif player == Player.TWO:
            self.player_two_health_text_label.text = (
                f"Player {player}: {self.play_state.player_two.health} HP"
            )

    def _physics_process(self, delta_time: float) -> None:
        # if self.time % 60 == 0:
        #     Client.send_message_to_server(message="Message from client!")
        # self.time += 1
        # if Input.is_action_just_pressed(action_name="quit"):
        #     if self.server_started:
        #         Server.stop()
        #         self.server_started = False
        #     else:
        #         Server.start(port=55555)
        #         self.server_started = True

        # Update state
        self.play_state.player_two.frames_invincible_after_damage = max(
            0, self.play_state.player_two.frames_invincible_after_damage - 1
        )

        for collided_node in Collision.get_collided_nodes(self.player_one):
            if (
                collided_node == self.player_two
                and self.play_state.player_two.frames_invincible_after_damage <= 0
            ):
                if Input.is_action_just_pressed(action_name="weak_punch"):
                    self.play_state.player_two.health -= 1
                    self.play_state.player_two.frames_invincible_after_damage = 60
                    self._update_player_health_text(player=Player.TWO)

        # Save state
        self.play_state.save_state(
            player_one_node=self.player_one, player_two_node=self.player_two
        )
        # if self.play_state.current_frame % 60 == 0:
        #     print(f"seconds = {self.play_state.current_frame / 60}, frame = {self.play_state.current_frame}")
        self.play_state.current_frame += 1
        # print(self.play_state)
