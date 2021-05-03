#ifndef PYTHON_SOURCE_H
#define PYTHON_SOURCE_H

using PythonSource = const std::string;

static const PythonSource PYTHON_SOURCE_ROLL_MODULE = "";

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
    "       return Vector3(self.x - other.x, self.y - other.y)\n"
    "\n"
    "   def __add__(self, other):\n"
    "       return Vector3(self.x - other.x, self.y - other.y)\n"
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

    "\"roll.math\": \"\"\"\n"
    + PYTHON_SOURCE_MATH_MODULE +
    "\"\"\",\n"

    "\"roll.color\": \"\"\"\n"
    + PYTHON_SOURCE_COLOR_MODULE +
    "\"\"\",\n"

    "}\n"
    "\n"
    "game_source_importer = SourceImporter(modules=modules_to_import)\n"
    "";

#endif //PYTHON_SOURCE_H
