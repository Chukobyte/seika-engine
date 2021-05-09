from roll.node import Node2D
from roll.physics import Collision

class Player():
    ONE = 1
    TWO = 2

class State:
    def __init__(self, player: int):
        self.health = 10
        self.attack = 5

class PlayState:
    def __init__(self):
        self.player_one = State(player=Player.ONE)
        self.player_two = State(player=Player.TWO)

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
            self.player_one_health_text_label.text = f"Player {player}: {self.play_state.player_one.health} HP"
        elif player == Player.TWO:
            self.player_two_health_text_label.text = f"Player {player}: {self.play_state.player_two.health} HP"

    def _physics_process(self, delta_time: float) -> None:
        for collided_node in Collision.get_collided_nodes(self.player_one):
            if collided_node == self.player_two:
                self.play_state.player_two.health -= 1
                self._update_player_health_text(player=Player.TWO)
