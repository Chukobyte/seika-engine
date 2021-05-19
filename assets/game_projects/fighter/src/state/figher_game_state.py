from roll.node import Node

from assets.game_projects.fighter.src.input_buffer import InputBuffer

class FighterUIState:
    def __init__(self):
        self.text_label = None


class FighterGameState:
    def __init__(self, node: Node, input_buffer: InputBuffer, fighter_ui_state: FighterUIState):
        self.node = node
        self.input_buffer = input_buffer
        self.fighter_ui_state = fighter_ui_state
