#ifndef PYTHON_MODULES_H
#define PYTHON_MODULES_H

#define PY_SSIZE_T_CLEAN

#include <Python.h>
#include <string>

class PythonModules {
  public:
    static PyObject* engine_exit(PyObject* self, PyObject* args, PyObject* kwargs);

    static PyObject* node2D_get_position(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* node2D_set_position(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* node2D_add_to_position(PyObject* self, PyObject* args, PyObject* kwargs);

    static PyObject* input_add_action(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* input_is_action_pressed(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* input_is_action_just_pressed(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* input_is_action_just_released(PyObject* self, PyObject* args, PyObject* kwargs);
};

static struct PyMethodDef rollApiMethods[] = {
    // ENGINE
    {
        "engine_exit", (PyCFunction) PythonModules::engine_exit,
        METH_VARARGS | METH_KEYWORDS, "Exits the engine."
    },
    // NODE2D
    {
        "node2D_get_position", (PyCFunction) PythonModules::node2D_get_position,
        METH_VARARGS | METH_KEYWORDS, "Gets a nodes position."
    },
    {
        "node2D_set_position", (PyCFunction) PythonModules::node2D_set_position,
        METH_VARARGS | METH_KEYWORDS, "Sets a nodes position."
    },
    {
        "node2D_add_to_position", (PyCFunction) PythonModules::node2D_add_to_position,
        METH_VARARGS | METH_KEYWORDS, "Adds to a nodes position."
    },
    // INPUT
    {
        "input_add_action", (PyCFunction) PythonModules::input_add_action,
        METH_VARARGS | METH_KEYWORDS, "Adds action input."
    },
    {
        "input_is_action_pressed", (PyCFunction) PythonModules::input_is_action_pressed,
        METH_VARARGS | METH_KEYWORDS, "Checks if action is pressed."
    },
    {
        "input_is_action_just_pressed", (PyCFunction) PythonModules::input_is_action_just_pressed,
        METH_VARARGS | METH_KEYWORDS, "Checks if action has been just pressed."
    },
    {
        "input_is_action_just_released", (PyCFunction) PythonModules::input_is_action_just_released,
        METH_VARARGS | METH_KEYWORDS, "Checks if action has been just released."
    },

    {nullptr, nullptr, 0,nullptr },
};

static struct PyModuleDef rollEngineAPIModDef = {
    PyModuleDef_HEAD_INIT, "roll_engine_api", nullptr, -1, rollApiMethods,
    nullptr, nullptr, nullptr, nullptr
};

static char *engineExitKWList[] = {"code", nullptr};

static char *nodeGetEntityKWList[] = {"entity_id", nullptr};

static char *node2DUpdatePositionKWList[] = {"entity_id", "x", "y", nullptr};

static char *inputAddActionKWList[] = {"action_name", "value", nullptr};
static char *inputActionCheckKWList[] = {"action_name", nullptr};

static PyObject* PyInit_rollEngineAPI(void) {
    return PyModule_Create(&rollEngineAPIModDef);
}

#endif //PYTHON_MODULES_H
