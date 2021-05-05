#ifndef PYTHON_SOURCE_H
#define PYTHON_SOURCE_H

using PythonSource = const std::string;

static const PythonSource PYTHON_SOURCE_ROLL_MODULE = "";

static const PythonSource  PYTHON_SOURCE_ENGINE_MODULE =
    "import roll_engine_api\n"
    "\n"
    "class Engine:\n"
    "   @staticmethod\n"
    "   def exit(code: int = 0) -> None:\n"
    "       roll_engine_api.engine_exit(code=code)\n"
    "\n"
    "";

static const PythonSource PYTHON_SOURCE_AUDIO_MODULE =
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

static const PythonSource PYTHON_SOURCE_MATH_MODULE =
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
    "   def __sub__(self, other):\n"
    "       return Vector2(self.x - other.x, self.y - other.y)\n"
    "\n"
    "   def __add__(self, other):\n"
    "       return Vector2(self.x - other.x, self.y - other.y)\n"
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
    "";

static const PythonSource PYTHON_SOURCE_COLOR_MODULE =
    "class Color:\n"
    "   def __init__(self, r=0.0, g=0.0, b=0.0, a=1.0):\n"
    "       self.r = r\n"
    "       self.g = g\n"
    "       self.b = b\n"
    "       self.a = a\n"
    "\n"
    "";

static const PythonSource PYTHON_SOURCE_INPUT_MODULE =
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

static const PythonSource PYTHON_SOURCE_CAMERA_MODULE =
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

static const PythonSource PYTHON_SOURCE_NODE_MODULE =
    "import roll_engine_api\n"
    "from roll.math import Vector2\n"
    "\n"
    "class Node:\n"
    "   def __init__(self, entity_id: int) -> None:\n"
    "       self.entity_id = entity_id\n"
    "\n"
    "def __eq__(self, other) -> bool:\n"
    "   if self.entity_id == other.entity_id:\n"
    "       return True\n"
    "   else:\n"
    "       return False\n"
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
    "";

static const PythonSource PYTHON_SOURCE_LOAD_SOURCE_IMPORTER_SNIPPET =
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

static const PythonSource PYTHON_SOURCE_IMPORT_ENGINE_MODULE_SNIPPET =
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

    "}\n"
    "\n"
    "game_source_importer = SourceImporter(modules=modules_to_import)\n"
    "";

#endif //PYTHON_SOURCE_H
