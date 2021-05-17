#ifndef PYTHON_SOURCE_H
#define PYTHON_SOURCE_H

using PythonSource = const std::string&;

static PythonSource PYTHON_SOURCE_ROLL_MODULE = "";

static PythonSource  PYTHON_SOURCE_ENGINE_MODULE =
    "import roll_engine_api\n"
    "\n"
    "class Engine:\n"
    "   @staticmethod\n"
    "   def exit(code: int = 0) -> None:\n"
    "       roll_engine_api.engine_exit(code=code)\n"
    "\n"
    "   @staticmethod\n"
    "   def get_fps() -> float:\n"
    "       return roll_engine_api.engine_get_fps()\n"
    "\n"
    "";

static PythonSource PYTHON_SOURCE_AUDIO_MODULE =
    "import roll_engine_api\n"
    "class Audio:\n"
    "   @staticmethod\n"
    "   def play_music(music_id: str) -> None:\n"
    "       roll_engine_api.audio_play_music(music_id=music_id)\n"
    "\n"
    "   @staticmethod\n"
    "   def stop_music() -> None:\n"
    "       roll_engine_api.audio_stop_music()\n"
    "\n"
    "   @staticmethod\n"
    "   def set_music_volume(volume: int) -> None:\n"
    "       roll_engine_api.audio_set_music_volume(volume=volume)\n"
    "\n"
    "   @staticmethod\n"
    "   def play_sound(sound_id: str) -> None:\n"
    "       roll_engine_api.audio_play_sound(sound_id=sound_id)\n"
    "\n"
    "   @staticmethod\n"
    "   def set_sound_volume(volume: int) -> None:\n"
    "       roll_engine_api.audio_set_sound_volume(volume=volume)\n"
    "\n"
    "   @staticmethod\n"
    "   def set_all_volume(volume: int) -> None:\n"
    "       roll_engine_api.audio_set_all_volume(volume=volume)\n"
    "\n"
    "";

static PythonSource PYTHON_SOURCE_MATH_MODULE =
    "class Vector2:\n"
    "   def __init__(self, x=0.0, y=0.0):\n"
    "       self.x = x\n"
    "       self.y = y\n"
    "\n"
    "   def dot_product(self, other) -> float:\n"
    "       return (self.x * other.x) + (self.y * other.y)\n"
    "\n"
    "   def __eq__(self, other) -> bool:\n"
    "       if self.x == other.x and self.y == other.y:\n"
    "           return True\n"
    "       else:\n"
    "           return False\n"
    "\n"
    "   def __gt__(self, other) -> bool:\n"
    "       if self.x + self.y > other.x + other.y:\n"
    "           return True\n"
    "       else:\n"
    "           return False\n"
    "\n"
    "   def __lt__(self, other) -> bool:\n"
    "       if self.x + self.y < other.x + other.y:\n"
    "           return True\n"
    "       else:\n"
    "           return False\n"
    "\n"
    "   def __sub__(self, other):\n"
    "       return Vector2(self.x - other.x, self.y - other.y)\n"
    "\n"
    "   def __add__(self, other):\n"
    "       return Vector2(self.x + other.x, self.y + other.y)\n"
    "\n"
    "   def __str__(self):\n"
    "       return f\"({self.x}, {self.y})\"\n"
    "\n"
    "   def __repr__(self):\n"
    "       return f\"({self.x}, {self.y})\"\n"
    "\n"
    "   @staticmethod\n"
    "   def ZERO():\n"
    "       return Vector2(0.0, 0.0)\n"
    "\n"
    "   @staticmethod\n"
    "   def LEFT():\n"
    "       return Vector2(-1.0, 0.0)\n"
    "\n"
    "   @staticmethod\n"
    "   def RIGHT():\n"
    "       return Vector2(1.0, 0.0)\n"
    "\n"
    "   @staticmethod\n"
    "   def UP():\n"
    "       return Vector2(0.0, -1.0)\n"
    "\n"
    "   @staticmethod\n"
    "   def DOWN():\n"
    "       return Vector2(0.0, 1.0)\n"
    "\n"
    "class Vector3:\n"
    "   def __init__(self, x=0.0, y=0.0, z=0.0):\n"
    "       self.x = x\n"
    "       self.y = y\n"
    "       self.z = z\n"
    "\n"
    "class Rect2:\n"
    "   def __init__(self, x=0.0, y=0.0, w=0.0, h=0.0):\n"
    "       self.x = x\n"
    "       self.y = y\n"
    "       self.w = w\n"
    "       self.h = h\n"
    "\n"
    "   def __str__(self):\n"
    "       return f\"({self.x}, {self.y}, {self.w}, {self.h})\"\n"
    "\n"
    "   def __repr__(self):\n"
    "       return f\"({self.x}, {self.y}, {self.w}, {self.h})\"\n"
    "\n"
    "   @property\n"
    "   def position(self) -> Vector2:\n"
    "       return Vector2(self.x, self.y)\n"
    "\n"
    "   @position.setter\n"
    "   def position(self, value: Vector2) -> None:\n"
    "       self.x = value.x\n"
    "       self.y = value.y\n"
    "\n"
    "   @property\n"
    "   def size(self) -> Vector2:\n"
    "       return Vector2(self.w, self.h)\n"
    "\n"
    "   @size.setter\n"
    "   def size(self, value: Vector2) -> None:\n"
    "       self.w = value.x\n"
    "       self.h = value.y\n"
    "\n"
    "";

static PythonSource PYTHON_SOURCE_COLOR_MODULE =
    "class Color:\n"
    "   def __init__(self, r=0.0, g=0.0, b=0.0, a=1.0):\n"
    "       self.r = r\n"
    "       self.g = g\n"
    "       self.b = b\n"
    "       self.a = a\n"
    "\n"
    "   def __str__(self):\n"
    "       return f\"({self.r}, {self.g}, {self.b}, {self.a})\"\n"
    "\n"
    "   def __repr__(self):\n"
    "       return f\"({self.r}, {self.g}, {self.b}, {self.a})\"\n"
    "\n"
    "";

static PythonSource PYTHON_SOURCE_INPUT_MODULE =
    "import roll_engine_api\n"
    "\n"
    "class Input:\n"
    "   @staticmethod\n"
    "   def add_action(action_name: str, value: str) -> None:\n"
    "       roll_engine_api.input_add_action(action_name=action_name, value=value)\n"
    "\n"
    "   @staticmethod\n"
    "   def is_action_pressed(action_name: str) -> bool:\n"
    "       return roll_engine_api.input_is_action_pressed(action_name=action_name)\n"
    "\n"
    "   @staticmethod\n"
    "   def is_action_just_pressed(action_name: str) -> bool:\n"
    "       return roll_engine_api.input_is_action_just_pressed(action_name=action_name)\n"
    "\n"
    "   @staticmethod\n"
    "   def is_action_just_released(action_name: str) -> bool:\n"
    "       return roll_engine_api.input_is_action_just_released(action_name=action_name)\n"
    "\n"
    "class Mouse:\n"
    "   LEFT_BUTTON = \"mb_left\"\n"
    "   RIGHT_BUTTON = \"mb_right\"\n"
    "\n"
    "class Keyboard:\n"
    "   NUM_0 = \"0\"\n"
    "   NUM_1 = \"1\"\n"
    "   NUM_2 = \"2\"\n"
    "   NUM_3 = \"3\"\n"
    "   NUM_4 = \"4\"\n"
    "   NUM_5 = \"5\"\n"
    "   NUM_6 = \"6\"\n"
    "   NUM_7 = \"7\"\n"
    "   NUM_8 = \"8\"\n"
    "   NUM_9 = \"9\"\n"
    "\n"
    "   A = \"a\"\n"
    "   B = \"b\"\n"
    "   C = \"c\"\n"
    "   D = \"d\"\n"
    "   E = \"e\"\n"
    "   F = \"f\"\n"
    "   G = \"g\"\n"
    "   H = \"h\"\n"
    "   I = \"i\"\n"
    "   J = \"j\"\n"
    "   K = \"k\"\n"
    "   L = \"l\"\n"
    "   M = \"m\"\n"
    "   N = \"n\"\n"
    "   O = \"o\"\n"
    "   P = \"p\"\n"
    "   Q = \"q\"\n"
    "   R = \"r\"\n"
    "   S = \"s\"\n"
    "   T = \"t\"\n"
    "   U = \"u\"\n"
    "   V = \"v\"\n"
    "   W = \"w\"\n"
    "   X = \"x\"\n"
    "   Y = \"y\"\n"
    "   Z = \"z\"\n"
    "\n"
    "   UP = \"up\"\n"
    "   DOWN = \"down\"\n"
    "   LEFT = \"left\"\n"
    "   RIGHT = \"right\"\n"
    "   SPACE = \"space\"\n"
    "   ESC = \"esc\"\n"
    "   RETURN = \"return\"\n"
    "\n"
    "   F1 = \"f1\"\n"
    "   F2 = \"f2\"\n"
    "   F3 = \"f3\"\n"
    "   F4 = \"f4\"\n"
    "   F5 = \"f5\"\n"
    "   F6 = \"f6\"\n"
    "   F7 = \"f7\"\n"
    "   F8 = \"f8\"\n"
    "   F9 = \"f9\"\n"
    "   F10 = \"f10\"\n"
    "   F11 = \"f11\"\n"
    "   F12 = \"f12\"\n"
    "\n";

static PythonSource PYTHON_SOURCE_CAMERA_MODULE =
    "import roll_engine_api\n"
    "from roll.math import Vector2\n"
    "\n"
    "class Camera:\n"
    "   @staticmethod\n"
    "   def set_zoom(zoom: Vector2) -> None:\n"
    "       roll_engine_api.camera_set_zoom(zoom.x, zoom.y)\n"
    "\n"
    "   @staticmethod\n"
    "   def set_viewport_position(position: Vector2) -> None:\n"
    "       roll_engine_api.camera_set_viewport_position(position.x, position.y)\n"
    "\n"
    "";

static PythonSource PYTHON_SOURCE_NODE_MODULE =
    "from enum import Enum\n"
    "from typing import Optional\n"
    "import roll_engine_api\n"
    "from roll.math import Vector2, Rect2\n"
    "from roll.color import Color\n"
    "\n"
    "class NodeType(str, Enum):\n"
    "   NODE = \"Node\"\n"
    "   NODE2D = \"Node2D\"\n"
    "   SPRITE = \"Sprite\"\n"
    "   ANIMATED_SPRITE = \"AnimatedSprite\"\n"
    "   TEXT_LABEL = \"TextLabel\"\n"
    "   COLLISION_SHAPE2D = \"CollisionShape2D\"\n"
    "\n"
    "class Node:\n"
    "   def __init__(self, entity_id: int) -> None:\n"
    "       self.entity_id = entity_id\n"
    "\n"
    "   def __eq__(self, other) -> bool:\n"
    "       if self.entity_id == other.entity_id:\n"
    "           return True\n"
    "       else:\n"
    "           return False\n"
    "\n"
    "   @classmethod\n"
    "   def extract_valid_inheritance_node(cls) -> str:\n"
    "       valid_node_type_list = [e.value for e in NodeType]\n"
    "       for class_path in cls.__mro__:\n"
    "           if class_path.__name__ in valid_node_type_list:\n"
    "               return class_path.__name__\n"
    "       return \"\"\n"
    "\n"
    "   @staticmethod\n"
    "   def parse_scene_node_from_engine(scene_node):\n"
    "       if isinstance(scene_node, Node):\n"
    "           return scene_node\n"
    "       else:\n"
    "           node_type = scene_node[0]\n"
    "           entity_id = scene_node[1]\n"
    "           node_class = globals()[node_type]\n"
    "           instance = node_class(entity_id=entity_id)\n"
    "           return instance\n"
    "\n"
    "   @classmethod\n"
    "   def new(cls):\n"
    "       return roll_engine_api.node_new(\n"
    "           class_path=f\"{__name__}\",\n"
    "           class_name=f\"{__class__.__name__}\",\n"
    "           node_type=f\"{cls.extract_valid_inheritance_node()}\",\n"
    "       )\n"
    "\n"
    "   def add_child(self, child_node) -> None:\n"
    "       roll_engine_api.node_add_child(parent_entity_id=self.entity_id, child_entity_id=child_node.entity_id)\n"
    "\n"
    "   def get_node(self, name: str):\n"
    "       node = roll_engine_api.node_get_node(name=name)\n"
    "       if not node:\n"
    "           return None\n"
    "       return self.parse_scene_node_from_engine(scene_node=node)\n"
    "\n"
    "   def queue_deletion(self) -> None:\n"
    "       roll_engine_api.node_queue_deletion(entity_id = self.entity_id)\n"
    "\n"
    "   def create_signal(self, signal_id: str) -> None:\n"
    "       roll_engine_api.node_signal_create(entity_id=self.entity_id, signal_id=signal_id)\n"
    "\n"
    "   def connect_signal(self, signal_id: str, listener_node, function_name: str) -> None:\n"
    "       roll_engine_api.node_signal_connect(\n"
    "           entity_id=self.entity_id,\n"
    "           signal_id=signal_id,\n"
    "           listener_entity_id=listener_node.entity_id,\n"
    "           function_name=function_name,\n"
    "       )\n"
    "\n"
    "   def emit_signal(self, signal_id: str, args=[]) -> None:\n"
    "       roll_engine_api.node_signal_emit(entity_id=self.entity_id, signal_id=signal_id, args=args)\n"
    "\n"
    "class Timer(Node):\n"
    "   @property\n"
    "   def wait_time(self) -> float:\n"
    "        return roll_engine_api.timer_get_wait_time(entity_id=self.entity_id)\n"
    "\n"
    "   @wait_time.setter\n"
    "   def wait_time(self, value: float) -> None:\n"
    "       roll_engine_api.timer_set_wait_time(entity_id=self.entity_id, wait_time=value)\n"
    "\n"
    "   def get_wait_time(self) -> float:\n"
    "       return roll_engine_api.timer_get_wait_time(entity_id=self.entity_id)\n"
    "\n"
    "   def set_wait_time(self, wait_time: float) -> None:\n"
    "       roll_engine_api.timer_set_wait_time(\n"
    "           entity_id=self.entity_id, wait_time=wait_time\n"
    "       )\n"
    "\n"
    "   @property\n"
    "   def time_left(self) -> float:\n"
    "       return roll_engine_api.timer_get_time_left(entity_id=self.entity_id)\n"
    "\n"
    "   def get_time_left(self) -> float:\n"
    "       return roll_engine_api.timer_get_time_left(entity_id=self.entity_id)\n"
    "\n"
    "   @property\n"
    "   def loops(self) -> bool:\n"
    "       return roll_engine_api.timer_get_loops(entity_id=self.entity_id)\n"
    "\n"
    "   @loops.setter\n"
    "   def loops(self, value: bool) -> None:\n"
    "       roll_engine_api.timer_set_loops(entity_id=self.entity_id, loops=value)\n"
    "\n"
    "   def does_loop(self) -> bool:\n"
    "       return roll_engine_api.timer_get_loops(entity_id=self.entity_id)\n"
    "\n"
    "   def set_loop(self, does_loop: bool) -> None:\n"
    "       roll_engine_api.timer_set_loops(entity_id=self.entity_id, loops=does_loop)\n"
    "\n"
    "   def start(self, wait_time: Optional[float] = None) -> None:\n"
    "       if wait_time:\n"
    "           roll_engine_api.timer_set_wait_time(\n"
    "               entity_id=self.entity_id, wait_time=wait_time\n"
    "           )\n"
    "       roll_engine_api.timer_start_timer(entity_id=self.entity_id)\n"
    "\n"
    "   def stop(self) -> None:\n"
    "       roll_engine_api.timer_stop_timer(entity_id=self.entity_id)\n"
    "\n"
    "   @property\n"
    "   def is_stopped(self) -> bool:\n"
    "       return roll_engine_api.timer_is_stopped(entity_id=self.entity_id)\n"
    "\n"
    "   def pause(self) -> None:\n"
    "       roll_engine_api.timer_pause_timer(entity_id=self.entity_id)\n"
    "\n"
    "   def resume(self) -> None:\n"
    "       roll_engine_api.timer_resume_timer(entity_id=self.entity_id)\n"
    "\n"
    "   @property\n"
    "   def is_paused(self) -> bool:\n"
    "       return roll_engine_api.timer_is_paused(entity_id=self.entity_id)\n"
    "\n"
    "class Node2D(Node):\n"
    "   def set_position(self, value: Vector2) -> None:\n"
    "       roll_engine_api.node2D_set_position(entity_id=self.entity_id, x=value.x, y=value.y)\n"
    "\n"
    "   def add_to_position(self, value: Vector2) -> None:\n"
    "       roll_engine_api.node2D_add_to_position(entity_id=self.entity_id, x=value.x, y=value.y)\n"
    "\n"
    "   def get_position(self) -> Vector2:\n"
    "       px, py = roll_engine_api.node2D_get_position(entity_id=self.entity_id)\n"
    "       return Vector2(px, py)\n"
    "\n"
    "   @property\n"
    "   def position(self) -> Vector2:\n"
    "       px, py = roll_engine_api.node2D_get_position(entity_id=self.entity_id)\n"
    "       return Vector2(px, py)\n"
    "\n"
    "   @position.setter\n"
    "   def position(self, value: Vector2) -> None:\n"
    "       roll_engine_api.node2D_set_position(entity_id=self.entity_id, x=value.x, y=value.y)\n"
    "\n"
    "class Sprite(Node2D):\n"
    "   @property\n"
    "   def flip_h(self) -> bool:\n"
    "       return roll_engine_api.sprite_get_flip_h(entity_id=self.entity_id)\n"
    "\n"
    "   @flip_h.setter\n"
    "   def flip_h(self, value: bool) -> None:\n"
    "       roll_engine_api.sprite_set_flip_h(entity_id=self.entity_id, flip_h=value)\n"
    "\n"
    "   @property\n"
    "   def flip_v(self) -> bool:\n"
    "       return roll_engine_api.sprite_get_flip_v(entity_id=self.entity_id)\n"
    "\n"
    "   @flip_v.setter\n"
    "   def flip_v(self, value: bool) -> None:\n"
    "       roll_engine_api.sprite_set_flip_v(entity_id=self.entity_id, flip_v=value)\n"
    "\n"
    "class AnimatedSprite(Node2D):\n"
    "   def play(self, animation_name: str) -> None:\n"
    "       roll_engine_api.animated_sprite_play(\n"
    "           entity_id=self.entity_id, animation_name=animation_name\n"
    "       )\n"
    "\n"
    "   def stop(self) -> None:\n"
    "       roll_engine_api.animated_sprite_stop(entity_id=self.entity_id)\n"
    "\n"
    "   @property\n"
    "   def is_playing(self) -> bool:\n"
    "       return roll_engine_api.animated_is_playing(entity_id=self.entity_id)\n"
    "\n"
    "   @property\n"
    "   def flip_h(self) -> bool:\n"
    "       return roll_engine_api.animated_sprite_get_flip_h(entity_id=self.entity_id)\n"
    "\n"
    "   @flip_h.setter\n"
    "   def flip_h(self, value: bool) -> None:\n"
    "       roll_engine_api.animated_sprite_set_flip_h(entity_id=self.entity_id, flip_h=value)\n"
    "\n"
    "   @property\n"
    "   def flip_v(self) -> bool:\n"
    "       return roll_engine_api.animated_sprite_get_flip_v(entity_id=self.entity_id)\n"
    "\n"
    "   @flip_v.setter\n"
    "   def flip_v(self, value: bool) -> None:\n"
    "       roll_engine_api.animated_sprite_set_flip_v(entity_id=self.entity_id, flip_v=value)\n"
    "\n"
    "class TextLabel(Node2D):\n"
    "   @property\n"
    "   def text(self) -> str:\n"
    "       return roll_engine_api.text_label_get_text(entity_id=self.entity_id)\n"
    "\n"
    "   @text.setter\n"
    "   def text(self, value: str) -> None:\n"
    "       roll_engine_api.text_label_set_text(entity_id=self.entity_id, text=value)\n"
    "\n"
    "   def get_text(self) -> str:\n"
    "       return roll_engine_api.text_label_get_text(entity_id=self.entity_id)\n"
    "\n"
    "   def set_text(self, text: str) -> None:\n"
    "       roll_engine_api.text_label_set_text(entity_id=self.entity_id, text=text)\n"
    "\n"
    "   @property\n"
    "   def color(self) -> Color:\n"
    "       red, green, blue, alpha = roll_engine_api.text_label_get_color(\n"
    "           entity_id=self.entity_id\n"
    "       )\n"
    "       return Color(r=red, g=green, b=blue, a=alpha)\n"
    "\n"
    "   @color.setter\n"
    "   def color(self, value: Color) -> None:\n"
    "       roll_engine_api.text_label_set_color(\n"
    "           entity_id=self.entity_id,\n"
    "           red=value.r,\n"
    "           green=value.g,\n"
    "           blue=value.b,\n"
    "           alpha=value.a,\n"
    "       )\n"
    "\n"
    "class CollisionShape2D(Node2D):\n"
    "   @property\n"
    "   def collider_rect(self) -> Rect2:\n"
    "       x, y, w, h = roll_engine_api.collision_shape2d_get_collider_rect(\n"
    "           entity_id=self.entity_id\n"
    "       )\n"
    "       return Rect2(x=x, y=y, w=w, h=h)\n"
    "\n"
    "   @collider_rect.setter\n"
    "   def collider_rect(self, value: Rect2) -> None:\n"
    "       roll_engine_api.collision_shape2d_set_collider_rect(\n"
    "           entity_id=self.entity_id, x=value.x, y=value.y, w=value.w, h=value.h\n"
    "       )\n"
    "\n"
    "";

static PythonSource PYTHON_SOURCE_PHYSICS_MODULE =
    "import roll_engine_api\n"
    "from roll.node import Node, Timer, Node2D, Sprite, AnimatedSprite, TextLabel\n"
    "\n"
    "class Collision:\n"
    "   @staticmethod\n"
    "   def check(node: Node) -> bool:\n"
    "       return roll_engine_api.collision_check(entity_id=node.entity_id)\n"
    "\n"
    "   @staticmethod\n"
    "   def get_collided_nodes(node : Node) -> list:\n"
    "       collided_nodes_from_engine = roll_engine_api.collision_get_collided_nodes(entity_id=node.entity_id)\n"
    "       collided_nodes = []\n"
    "       for collided_node in collided_nodes_from_engine:\n"
    "           collided_nodes.append(Node.parse_scene_node_from_engine(scene_node=collided_node))\n"
    "       return collided_nodes\n"
    "\n"
    "";

static PythonSource PYTHON_SOURCE_SCENE_MODULE =
    "import roll_engine_api\n"
    "from roll.node import Node, Timer, Node2D, Sprite, AnimatedSprite, TextLabel\n"
    "\n"
    "class SceneTree:\n"
    "   @staticmethod\n"
    "   def change_scene(scene_path: str) -> None:\n"
    "       roll_engine_api.scene_tree_change_scene(scene_path=scene_path)\n"
    "\n"
    "   @staticmethod\n"
    "   def get_current_scene_node() -> Node:\n"
    "       current_scene_node = roll_engine_api.scene_tree_get_current_scene_node()\n"
    "       return Node.parse_scene_node_from_engine(scene_node=current_scene_node)\n"
    "\n"
    "";

static PythonSource PYTHON_SOURCE_NETWORK_MODULE =
    "import roll_engine_api\n"
    "\n"
    "class Network:\n"
    "   @staticmethod\n"
    "   def connect_signal(signal_id: str, listener_node, function_name: str) -> None:\n"
    "       roll_engine_api.node_signal_connect(\n"
    "           entity_id=0,\n"
    "           signal_id=signal_id,\n"
    "           listener_entity_id=listener_node.entity_id,\n"
    "           function_name=function_name,\n"
    "       )\n"
    "\n"
    "   @staticmethod\n"
    "   def is_server() -> bool:\n"
    "       return roll_engine_api.network_is_server()\n"
    "\n"
    "class Server:\n"
    "   @staticmethod\n"
    "   def start(port: int) -> None:\n"
    "       roll_engine_api.server_start(port=port)\n"
    "\n"
    "   @staticmethod\n"
    "   def stop() -> None:\n"
    "       roll_engine_api.server_stop()\n"
    "\n"
    "   @staticmethod\n"
    "   def send_message_to_all_clients(message: str) -> None:\n"
    "       roll_engine_api.server_send_message_to_all_clients(message=message)\n"
    "\n"
    "class Client:\n"
    "   @staticmethod\n"
    "   def connect(endpoint: str, port: int) -> None:\n"
    "       roll_engine_api.client_connect(endpoint=endpoint, port=port)\n"
    "\n"
    "   @staticmethod\n"
    "   def disconnect() -> None:\n"
    "       roll_engine_api.client_disconnect()\n"
    "\n"
    "   @staticmethod\n"
    "   def send_message_to_server(message: str) -> None:\n"
    "       roll_engine_api.client_send_message_to_server(message=message)\n"
    "\n"
    "";

static PythonSource PYTHON_SOURCE_LOAD_SOURCE_IMPORTER_SNIPPET =
    "import sys\n"
    "import importlib\n"
    "import importlib.util\n"
    "\n"
    "module_name = \"source_importer\"\n"
    "source_code = \"\"\"\n"
    "import sys\n"
    "import importlib\n"
    "import importlib.util\n"
    "\n"
    "class SourceImporter:\n"
    "   def __init__(self, modules: dict):\n"
    "       self._modules = modules\n"
    "\n"
    "       for module_name in self._modules:\n"
    "           module_src = self._modules[module_name]\n"
    "           self.import_from_source(module_name, module_src)\n"
    "\n"
    "   def import_from_source(self, module_name: str, source_code: str):\n"
    "       spec = importlib.util.spec_from_loader(module_name, loader=None, is_package=False)\n"
    "       module = importlib.util.module_from_spec(spec)\n"
    "       exec(source_code, module.__dict__)\n"
    "       sys.modules[module_name] = module\n"
    "       return module\n"
    "\"\"\"\n"
    "\n"
    "# Load source importer module\n"
    "spec = importlib.util.spec_from_loader(module_name, loader=None, is_package=False)\n"
    "module = importlib.util.module_from_spec(spec)\n"
    "exec(source_code, module.__dict__)\n"
    "sys.modules[module_name] = module\n"
    "";

static PythonSource PYTHON_SOURCE_IMPORT_ENGINE_MODULE_SNIPPET =
    "from source_importer import SourceImporter\n"
    "\n"
    "modules_to_import = {\n"

    "\"roll\": \"\"\"\n"
    + PYTHON_SOURCE_ROLL_MODULE +
    "\"\"\",\n"

    "\"roll.engine\": \"\"\"\n"
    + PYTHON_SOURCE_ENGINE_MODULE +
    "\"\"\",\n"

    "\"roll.audio\": \"\"\"\n"
    + PYTHON_SOURCE_AUDIO_MODULE +
    "\"\"\",\n"

    "\"roll.math\": \"\"\"\n"
    + PYTHON_SOURCE_MATH_MODULE +
    "\"\"\",\n"

    "\"roll.color\": \"\"\"\n"
    + PYTHON_SOURCE_COLOR_MODULE +
    "\"\"\",\n"

    "\"roll.input\": \"\"\"\n"
    + PYTHON_SOURCE_INPUT_MODULE +
    "\"\"\",\n"

    "\"roll.camera\": \"\"\"\n"
    + PYTHON_SOURCE_CAMERA_MODULE +
    "\"\"\",\n"

    "\"roll.node\": \"\"\"\n"
    + PYTHON_SOURCE_NODE_MODULE +
    "\"\"\",\n"

    "\"roll.physics\": \"\"\"\n"
    + PYTHON_SOURCE_PHYSICS_MODULE +
    "\"\"\",\n"

    "\"roll.scene\": \"\"\"\n"
    + PYTHON_SOURCE_SCENE_MODULE +
    "\"\"\",\n"

    "\"roll.network\": \"\"\"\n"
    + PYTHON_SOURCE_NETWORK_MODULE +
    "\"\"\",\n"

    "}\n"
    "\n"
    "game_source_importer = SourceImporter(modules=modules_to_import)\n"
    "";

#endif //PYTHON_SOURCE_H
