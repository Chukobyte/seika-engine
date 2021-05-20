from roll.color import Color
from roll.math import Vector2, Rect2
from roll.node import Node

from assets.game_projects.fighter.src.hit_box import Attack
from assets.game_projects.fighter.src.input_buffer import InputBuffer
from assets.game_projects.fighter.src.state.game_state_manager import GameStateManager


class AttackManager:
    def __init__(self):
        self._player_attacks = {}
        self._collided_attack_entity_ids = []

    def add_attack(self, player: int, attack: Attack) -> None:
        self._player_attacks[player] = attack

    def _remove_node_active_attack(self, player: int) -> None:
        if self.has_attack(player=player):
            self._player_attacks[player].queue_deletion()
            self._player_attacks[player] = None

    def has_attack(self, player: int) -> bool:
        if player in self._player_attacks and self._player_attacks[player]:
            return True
        return False

    def node_has_attack(self, node: Node) -> bool:
        return self.has_attack(entity_id=node.entity_id)

    def process_frame(self) -> None:
        self._collided_attack_entity_ids.clear()
        for player in self._player_attacks:
            attack = self._player_attacks[player]
            if attack:
                if not attack.has_hit and attack.has_collided_with_anything():
                    attack.has_hit = True
                    self._collided_attack_entity_ids.append(player)
                attack.frame_life_time -= 1
                if attack.frame_life_time <= 0:
                    self._remove_node_active_attack(player=player)

    def get_entity_id_for_collided_attacks(self) -> list:
        return self._collided_attack_entity_ids


class FightSimulator:
    def __init__(self):
        self.attack_manager = AttackManager()

    def simulate_frame(self, frame: int, game_state_manager: GameStateManager) -> None:
        # TODO: Will separate general state processing into more steps once attack damage animations come into play
        self._process_general_state(frame=frame, game_state_manager=game_state_manager)

        self._resolve_attacks(game_state_manager=game_state_manager)

    def _process_general_state(
        self, frame: int, game_state_manager: GameStateManager
    ) -> None:
        for player_id in game_state_manager.game_state.player_states:
            player_state = game_state_manager.game_state.player_states[player_id]
            if player_state.input_buffer.is_empty():
                player_state.node.play(animation_name="idle")
            elif not self.attack_manager.has_attack(player=player_state.id):
                for input in player_state.input_buffer.get_frame_inputs(frame=frame):
                    if input == InputBuffer.Value.LEFT.value:
                        player_state.node.add_to_position(Vector2.LEFT())
                        player_state.node.play(animation_name="walk")
                    elif input == InputBuffer.Value.RIGHT.value:
                        player_state.node.add_to_position(Vector2.RIGHT())
                        player_state.node.play(animation_name="walk")
                    elif input == InputBuffer.Value.WEAK_PUNCH.value:
                        weak_punch_attack = Attack.new()
                        weak_punch_attack.collider_rect = Rect2(x=100, y=32, w=64, h=64)
                        weak_punch_attack.color = Color(1.0, 0.0, 0.0, 0.75)
                        player_state.node.add_child(child_node=weak_punch_attack)
                        weak_punch_attack.frame_life_time = 100
                        self.attack_manager.add_attack(
                            player=player_state.id, attack=weak_punch_attack
                        )

    def _resolve_attacks(self, game_state_manager: GameStateManager) -> None:
        self.attack_manager.process_frame()
        for player in self.attack_manager.get_entity_id_for_collided_attacks():
            # Only resolving damage for now
            hp_text_label = game_state_manager.ui_state.hp_labels[player]
            previous_hp = int(hp_text_label.text)
            damage = 1  # TODO: Will be based off of attack damage
            hp_text_label.text = str(previous_hp - damage)
