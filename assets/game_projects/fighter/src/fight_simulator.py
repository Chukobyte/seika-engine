from typing import Optional

from roll.node import Node
from roll.math import Vector2, Rect2
from roll.color import Color

from assets.game_projects.fighter.src.fight_state import PlayerStateData, UIState
from assets.game_projects.fighter.src.hit_box import Attack
from assets.game_projects.fighter.src.input_buffer import InputBuffer


class AttackManager:
    def __init__(self):
        self._player_attacks = {}
        self._collided_attack_entity_ids = []

    def add_attack(self, node: Node, attack: Attack) -> None:
        self._player_attacks[node.entity_id] = attack

    def _remove_node_active_attack(self, entity_id: int) -> None:
        if self.has_attack(entity_id=entity_id):
            self._player_attacks[entity_id].queue_deletion()
            self._player_attacks[entity_id] = None

    def has_attack(self, entity_id: int) -> bool:
        if entity_id in self._player_attacks and self._player_attacks[entity_id]:
            return True
        return False

    def node_has_attack(self, node: Node) -> bool:
        return self.has_attack(entity_id=node.entity_id)

    def process_frame(self) -> None:
        self._collided_attack_entity_ids.clear()
        for entity_id in self._player_attacks:
            attack = self._player_attacks[entity_id]
            if attack:
                if not attack.has_hit and attack.has_collided_with_anything():
                    attack.has_hit = True
                    self._collided_attack_entity_ids.append(entity_id)
                attack.frame_life_time -= 1
                if attack.frame_life_time <= 0:
                    self._remove_node_active_attack(entity_id=entity_id)

    def get_entity_id_for_collided_attacks(self) -> list:
        return self._collided_attack_entity_ids


class FightSimulator:
    def __init__(self):
        self.attack_manager = AttackManager()
        self.ui_state = UIState()

    def simulate_frame(
        self,
        frame: int,
        player_one_state_data: Optional[PlayerStateData] = None,
        player_two_state_data: Optional[PlayerStateData] = None,
    ) -> None:
        self.attack_manager.process_frame()
        # TODO: clean up
        for (
            attack_entity_id
        ) in self.attack_manager.get_entity_id_for_collided_attacks():
            if attack_entity_id == player_one_state_data.player_node.entity_id:
                hp_amount = int(self.ui_state.player_two_hp_text_label.text)
                damage = 1
                hp_amount -= damage
                self.ui_state.player_two_hp_text_label.text = str(hp_amount)
            elif (
                player_two_state_data
                and attack_entity_id == player_two_state_data.player_node.entity_id
            ):
                hp_amount = int(self.ui_state.player_one_hp_text_label.text)
                damage = 1
                hp_amount -= damage
                self.ui_state.player_one_hp_text_label.text = str(hp_amount)

        for player_state_data in [player_one_state_data, player_two_state_data]:
            if player_state_data:
                self._simulate_player_state(
                    frame=frame, player_state_data=player_state_data
                )

    def _simulate_player_state(
        self, frame: int, player_state_data: PlayerStateData
    ) -> None:
        if player_state_data.player_input_buffer.is_empty():
            player_state_data.player_node.play(animation_name="idle")
        else:
            for input in player_state_data.player_input_buffer.get_frame_inputs(
                frame=frame
            ):
                if not self.attack_manager.node_has_attack(
                    node=player_state_data.player_node
                ):
                    if input == InputBuffer.Value.LEFT.value:
                        player_state_data.player_node.add_to_position(Vector2.LEFT())
                        player_state_data.player_node.play(animation_name="walk")
                        # player_one_state_data.player_node.flip_h = True
                    elif input == InputBuffer.Value.RIGHT.value:
                        player_state_data.player_node.add_to_position(Vector2.RIGHT())
                        player_state_data.player_node.play(animation_name="walk")
                        # player_one_state_data.player_node.flip_h = False
                    elif input == InputBuffer.Value.WEAK_PUNCH.value:
                        # TODO: Implement weak punch
                        weak_punch_attack = Attack.new()
                        # weak_punch_attack.collider_rect = Rect2(x=64, y=0, w=64, h=64)
                        weak_punch_attack.collider_rect = Rect2(x=100, y=32, w=64, h=64)
                        weak_punch_attack.color = Color(1.0, 0.0, 0.0, 0.75)
                        player_state_data.player_node.add_child(
                            child_node=weak_punch_attack
                        )
                        weak_punch_attack.frame_life_time = 100
                        self.attack_manager.add_attack(
                            node=player_state_data.player_node, attack=weak_punch_attack
                        )

    def roll_back(self, frame: int, new_state) -> None:
        pass
