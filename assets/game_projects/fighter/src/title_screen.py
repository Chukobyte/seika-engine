from roll.node import Node2D
from roll.scene import SceneTree
from roll.input import Input
from roll.engine import Engine
from roll.color import Color


class MenuSelection:
    PLAY_LOCAL_COMPUTER = 0
    PLAY_LOCAL_HUMAN = 1
    PLAY_AS_HOST = 2
    PLAY_AS_CLIENT = 3


class SelectionList:
    def __init__(self, selections: list):
        self._list = selections
        self._index = 0

    def increment(self):
        self._index += 1
        if self._index >= len(self._list):
            self._index = 0
        return self._list[self._index]

    def decrement(self):
        self._index -= 1
        if self._index < 0:
            self._index = len(self._list) - 1
        return self._list[self._index]

    def get_current_item(self):
        return self._list[self._index]


class TitleScreen(Node2D):
    def _start(self) -> None:
        self.play_local_computer_text = self.get_node(name="PlayLocalComputerText")
        self.play_local_human_text = self.get_node(name="PlayLocalHumanText")
        self.play_as_host_text = self.get_node(name="PlayAsHostText")
        self.play_as_client_text = self.get_node(name="PlayAsClientText")

        self.selected_color = Color(1.0, 0.0, 0.0, 1.0)
        self.unselected_color = Color(0.0, 1.0, 1.0, 1.0)

        self.selection_list = SelectionList(
            selections=[
                MenuSelection.PLAY_LOCAL_COMPUTER,
                MenuSelection.PLAY_LOCAL_HUMAN,
                MenuSelection.PLAY_AS_HOST,
                MenuSelection.PLAY_AS_CLIENT,
            ]
        )
        self._update_menu_selection_labels(
            selection=self.selection_list.get_current_item()
        )

    def _update_menu_selection_labels(self, selection) -> None:
        if selection == MenuSelection.PLAY_LOCAL_COMPUTER:
            self.play_local_computer_text.color = self.selected_color
            self.play_local_human_text.color = self.unselected_color
            self.play_as_host_text.color = self.unselected_color
            self.play_as_client_text.color = self.unselected_color
        elif selection == MenuSelection.PLAY_LOCAL_HUMAN:
            self.play_local_computer_text.color = self.unselected_color
            self.play_local_human_text.color = self.selected_color
            self.play_as_host_text.color = self.unselected_color
            self.play_as_client_text.color = self.unselected_color
        elif selection == MenuSelection.PLAY_AS_HOST:
            self.play_local_computer_text.color = self.unselected_color
            self.play_local_human_text.color = self.unselected_color
            self.play_as_host_text.color = self.selected_color
            self.play_as_client_text.color = self.unselected_color
        elif selection == MenuSelection.PLAY_AS_CLIENT:
            self.play_local_computer_text.color = self.unselected_color
            self.play_local_human_text.color = self.unselected_color
            self.play_as_host_text.color = self.unselected_color
            self.play_as_client_text.color = self.selected_color

    def _physics_process(self, delta_time: float) -> None:
        if Input.is_action_just_pressed(action_name="quit"):
            Engine.exit()

        if Input.is_action_just_pressed(action_name="one_up"):
            self._update_menu_selection_labels(
                selection=self.selection_list.decrement()
            )
        elif Input.is_action_just_pressed(action_name="one_down"):
            self._update_menu_selection_labels(
                selection=self.selection_list.increment()
            )

        if Input.is_action_just_pressed(action_name="confirm"):
            SceneTree.change_scene(
                scene_path="assets/game_projects/fighter/scenes/main.json"
            )
