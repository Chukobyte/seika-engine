#ifndef PYTHON_MODULES_H
#define PYTHON_MODULES_H

#define PY_SSIZE_T_CLEAN

#include <Python.h>
#include <string>

class PythonModules {
  public:
    static PyObject* node2D_get_position(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* node2D_set_position(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* node2D_add_to_position(PyObject* self, PyObject* args, PyObject* kwargs);

    static PyObject* input_add_action(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* input_is_action_pressed(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* input_is_action_just_pressed(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* input_is_action_just_released(PyObject* self, PyObject* args, PyObject* kwargs);
};

static struct PyMethodDef rollApiMethods[] = {
    // NODE2D
    {
        "get_node2D_position", (PyCFunction) PythonModules::node2D_get_position,
        METH_VARARGS | METH_KEYWORDS, "Gets a nodes position."
    },
    {
        "set_node2D_position", (PyCFunction) PythonModules::node2D_set_position,
        METH_VARARGS | METH_KEYWORDS, "Sets a nodes position."
    },
    {
        "add_to_node2D_position", (PyCFunction) PythonModules::node2D_add_to_position,
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
};

static struct PyModuleDef rollEngineAPIModDef = {
    PyModuleDef_HEAD_INIT, "roll_engine_api", NULL, -1, rollApiMethods,
    NULL, NULL, NULL, NULL
};

static char *nodeGetEntityKWList[] = {"entity_id", NULL};

static char *node2DUpdatePositionKWList[] = {"entity_id", "x", "y", NULL};

static char *inputAddActionKWList[] = {"action_name", "value", NULL};
static char *inputActionCheckKWList[] = {"action_name", NULL};

static PyObject* PyInit_rollEngineAPI(void) {
    return PyModule_Create(&rollEngineAPIModDef);
}

#endif //PYTHON_MODULES_H
