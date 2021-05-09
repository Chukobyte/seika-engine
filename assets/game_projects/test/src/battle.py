from roll.node import Node2D
from roll.physics import Collision


class Player:
    ONE = 1
    TWO = 2


class PlayerState:
    def __init__(self, player: int):
        self.player = player
        self.health = 10
        self.attack = 5


class FrameState:
    def __init__(self, frame, player_one_health, player_two_health) -> None:
        self.frame = frame
        self.player_one_health = player_one_health
        self.player_two_health = player_two_health

    def __str__(self):
        data = {
            "frame": self.frame,
            "player_one_health": self.player_one_health,
            "player_two_health": self.player_two_health,
        }
        return f"{data}"

    def __repr__(self):
        data = {
            "frame": self.frame,
            "player_one_health": self.player_one_health,
            "player_two_health": self.player_two_health,
        }
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

    def save_state(self) -> None:
        self.frames[self.current_frame] = FrameState(
            frame=self.current_frame,
            player_one_health=self.player_one.health,
            player_two_health=self.player_two.health,
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
        for collided_node in Collision.get_collided_nodes(self.player_one):
            if collided_node == self.player_two:
                self.play_state.player_two.health -= 1
                self._update_player_health_text(player=Player.TWO)

        # Update state
        self.play_state.save_state()
        self.play_state.current_frame += 1
        # print(self.play_state)
