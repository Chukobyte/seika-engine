from seika.math import Vector2
from seika.node import AnimatedSprite, TextLabel

from assets.game_projects.fighter.src.input_buffer import InputBuffer
from assets.game_projects.fighter.src.model.fighter_direction import FighterDirection
from assets.game_projects.fighter.src.model.player import Player
from assets.game_projects.fighter.src.state.state_data import FrameStateData


class FighterActionState:
    WAITING = "waiting"
    ATTACKING = "attacking"
    GUARDING = "guarding"
    HIT_STUN = "hit_stun"
    KNOCKED_DOWN = "knocked_down"


class FighterStanceState:
    STANDING = "standing"
    CROUCHING = "crouching"
    IN_THE_AIR = "in_the_air"


class AnimationState:
    def __init__(self, node: AnimatedSprite):
        self.node = node
        self.current_frame = 0
        self.current_index = 0
        self.animation_name = ""
        self.frames_per_index = 0
        self.animation_frames = 0

    def set_animation(self, animation_name: str) -> None:
        if self.animation_name != animation_name:
            self.animation_name = animation_name
            self.node.set_animation(animation_name=animation_name)
            self.animation_frames = self.node.animation_frames
            self.frames_per_index = self.node.animation_speed / 10
            self.current_frame = 0
            self.current_index = 0

    def process_frame(self) -> None:
        self.node.frame = self.current_index
        if self.current_frame >= self.frames_per_index:
            self.current_index += 1
            if self.current_index >= self.animation_frames:
                self.current_index = 0
            self.current_frame = 0
        else:
            self.current_frame += 1


class PlayerState:
    def __init__(self, id: int):
        self.id = id
        self.node = None
        self.input_buffer = None
        self.animation_state = None

        self.direction = FighterDirection.RIGHT
        self.velocity = Vector2(0, 0)
        self.fighter_stance_state = FighterStanceState.STANDING
        self.fighter_action_state = FighterActionState.WAITING
        self.is_jumping = False
        self.jump_amount = 0


class GameState:
    def __init__(self):
        self.player_states = {
            Player.ONE: PlayerState(Player.ONE),
            Player.TWO: PlayerState(Player.TWO),
        }
        self.opponent_player = {
            Player.ONE: Player.TWO,
            Player.TWO: Player.ONE,
        }
        self.frame_states = {}

    def poll_input(self, frame: int) -> None:
        for player_number in self.player_states:
            player_state = self.player_states[player_number]
            if player_state and player_state.input_buffer:
                player_state.input_buffer.poll_client_inputs(frame=frame)

    def set_input_buffer(self, player: int, input_buffer: InputBuffer) -> None:
        self.player_states[player].input_buffer = input_buffer

    def set_player_state(self, player: int, state: PlayerState):
        self.player_states[player] = state

    def save_frame_state(self, frame_state_data: FrameStateData) -> None:
        self.frame_states[frame_state_data.frame] = frame_state_data


class UIState:
    def __init__(self):
        self.hp_labels = {
            Player.ONE: None,
            Player.TWO: None,
        }

    def set_hp_label(self, player: int, label: TextLabel) -> None:
        self.hp_labels[player] = label
