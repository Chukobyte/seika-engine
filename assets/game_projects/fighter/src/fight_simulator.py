from roll.color import Color
from roll.math import Vector2, Rect2
from roll.node import Node

from assets.game_projects.fighter.src.hit_box import Attack
from assets.game_projects.fighter.src.input_buffer import InputBuffer
from assets.game_projects.fighter.src.model.animation_name import AnimationName
from assets.game_projects.fighter.src.model.fighter_direction import FighterDirection
from assets.game_projects.fighter.src.model.player import Player
from assets.game_projects.fighter.src.state.game_state import FighterActionState
from assets.game_projects.fighter.src.state.game_state_manager import GameStateManager


class AttackFrameResult:
    def __init__(self, collided_entity_ids: list):
        self.collided_entity_ids = collided_entity_ids


class AttackManager:
    def __init__(self):
        self._player_attacks = {}

    def add_attack(self, player: int, attack: Attack) -> None:
        self._player_attacks[player] = attack

    def _remove_node_active_attack(
        self, player: int, game_state_manager: GameStateManager
    ) -> None:
        if self.has_attack(player=player):
            self._player_attacks[player].queue_deletion()
            self._player_attacks[player] = None
            player_state = game_state_manager.game_state.player_states[player]
            player_state.fighter_action_state = FighterActionState.WAITING

    def has_attack(self, player: int) -> bool:
        if player in self._player_attacks and self._player_attacks[player]:
            return True
        return False

    def process_frame(self, game_state_manager: GameStateManager) -> AttackFrameResult:
        collided_attack_entity_ids = []
        for player in self._player_attacks:
            attack = self._player_attacks[player]
            if attack:
                if not attack.has_hit and attack.has_collided_with_anything():
                    attack.has_hit = True
                    collided_attack_entity_ids.append(player)
                attack.frame_life_time -= 1
                if attack.frame_life_time <= 0:
                    self._remove_node_active_attack(
                        player=player, game_state_manager=game_state_manager
                    )
        return AttackFrameResult(collided_entity_ids=collided_attack_entity_ids)


class FightSimulator:
    def __init__(self):
        self.attack_manager = AttackManager()

    def simulate_frame(self, frame: int, game_state_manager: GameStateManager) -> None:
        self._process_general_state(frame=frame, game_state_manager=game_state_manager)

        self._resolve_attacks(game_state_manager=game_state_manager)

        self._update_animations(game_state_manager=game_state_manager)

    def _process_general_state(
        self, frame: int, game_state_manager: GameStateManager
    ) -> None:
        for player_id in game_state_manager.game_state.player_states:
            player_state = game_state_manager.game_state.player_states[player_id]
            if player_state.input_buffer.is_empty():
                player_state.animation_state.set_animation(AnimationName.IDLE)
            else:
                if player_state.fighter_action_state == FighterActionState.WAITING:
                    for input in player_state.input_buffer.get_frame_inputs(
                        frame=frame
                    ):
                        if input == InputBuffer.Value.LEFT.value:
                            player_state.node.add_to_position(Vector2.LEFT())
                            player_state.animation_state.set_animation(
                                AnimationName.WALK
                            )
                        elif input == InputBuffer.Value.RIGHT.value:
                            player_state.node.add_to_position(Vector2.RIGHT())
                            player_state.animation_state.set_animation(
                                AnimationName.WALK
                            )
                        elif input == InputBuffer.Value.WEAK_PUNCH.value:
                            weak_punch_attack = Attack.new()
                            weak_punch_attack.collider_rect = Rect2(
                                x=32 + (65 * player_state.direction), y=32, w=64, h=64
                            )
                            weak_punch_attack.color = Color(1.0, 0.0, 0.0, 0.75)
                            player_state.node.add_child(child_node=weak_punch_attack)
                            player_state.fighter_action_state = (
                                FighterActionState.ATTACKING
                            )
                            weak_punch_attack.frame_life_time = 100
                            self.attack_manager.add_attack(
                                player=player_state.id, attack=weak_punch_attack
                            )

    def _resolve_attacks(self, game_state_manager: GameStateManager) -> None:
        attack_frame_result = self.attack_manager.process_frame(
            game_state_manager=game_state_manager
        )
        for player in attack_frame_result.collided_entity_ids:
            # Only resolving damage for now
            opponent_player = game_state_manager.game_state.opponent_player[player]
            hp_text_label = game_state_manager.ui_state.hp_labels[opponent_player]
            previous_hp = int(hp_text_label.text)
            damage = 1  # TODO: Will be based off of attack damage
            hp_text_label.text = str(previous_hp - damage)

    def _update_animations(self, game_state_manager: GameStateManager) -> None:
        for player_id in game_state_manager.game_state.player_states:
            player_state = game_state_manager.game_state.player_states[player_id]
            player_state.animation_state.process_frame()

        # Update direction facing
        player_one_state = game_state_manager.game_state.player_states[Player.ONE]
        player_two_state = game_state_manager.game_state.player_states[Player.TWO]
        player_one_position_x = player_one_state.node.position.x
        player_two_position_x = player_two_state.node.position.x

        if player_one_position_x < player_two_position_x:
            player_one_state.direction = FighterDirection.RIGHT
            player_one_state.node.flip_h = False
        else:
            player_one_state.direction = FighterDirection.LEFT
            player_one_state.node.flip_h = True

        if player_two_position_x < player_one_position_x:
            player_two_state.direction = FighterDirection.RIGHT
            player_two_state.node.flip_h = False
        else:
            player_two_state.direction = FighterDirection.LEFT
            player_two_state.node.flip_h = True
