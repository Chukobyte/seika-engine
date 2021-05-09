#ifndef PYTHON_MODULES_H
#define PYTHON_MODULES_H

#define PY_SSIZE_T_CLEAN

#include <Python.h>
#include <string>

class PythonModules {
  public:
    static PyObject* engine_exit(PyObject* self, PyObject* args, PyObject* kwargs);

    static PyObject* audio_play_music(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* audio_stop_music(PyObject* self, PyObject* args);
    static PyObject* audio_set_music_volume(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* audio_play_sound(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* audio_set_sound_volume(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* audio_set_all_volume(PyObject* self, PyObject* args, PyObject* kwargs);

    static PyObject* camera_set_zoom(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* camera_set_viewport_position(PyObject* self, PyObject* args, PyObject* kwargs);

    static PyObject* node_get_node(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* node_queue_deletion(PyObject* self, PyObject* args, PyObject* kwargs);

    static PyObject* node2D_get_position(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* node2D_set_position(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* node2D_add_to_position(PyObject* self, PyObject* args, PyObject* kwargs);

    static PyObject* text_label_get_text(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* text_label_set_text(PyObject* self, PyObject* args, PyObject* kwargs);

    static PyObject* collision_check(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* collision_get_collided_nodes(PyObject* self, PyObject* args, PyObject* kwargs);

    static PyObject* input_add_action(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* input_is_action_pressed(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* input_is_action_just_pressed(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* input_is_action_just_released(PyObject* self, PyObject* args, PyObject* kwargs);

    static PyObject* scene_tree_change_scene(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* scene_tree_get_current_scene_node(PyObject* self, PyObject* args);
};

static struct PyMethodDef rollApiMethods[] = {
    // ENGINE
    {
        "engine_exit", (PyCFunction) PythonModules::engine_exit,
        METH_VARARGS | METH_KEYWORDS, "Exits the engine."
    },
    // AUDIO
    {
        "audio_play_music", (PyCFunction) PythonModules::audio_play_music,
        METH_VARARGS | METH_KEYWORDS, "Plays music."
    },
    {
        "audio_stop_music", PythonModules::audio_stop_music,
        METH_VARARGS, "Stops music."
    },
    {
        "audio_set_music_volume", (PyCFunction) PythonModules::audio_set_music_volume,
        METH_VARARGS | METH_KEYWORDS, "Set music volume."
    },
    {
        "audio_play_sound", (PyCFunction) PythonModules::audio_play_sound,
        METH_VARARGS | METH_KEYWORDS, "Plays sound."
    },
    {
        "audio_set_sound_volume", (PyCFunction) PythonModules::audio_set_sound_volume,
        METH_VARARGS | METH_KEYWORDS, "Sets sound volume."
    },
    {
        "audio_set_all_volume", (PyCFunction) PythonModules::audio_set_all_volume,
        METH_VARARGS | METH_KEYWORDS, "Sets all sound volume."
    },
    // CAMERA
    {
        "camera_set_zoom", (PyCFunction) PythonModules::camera_set_zoom,
        METH_VARARGS | METH_KEYWORDS, "Sets camera zoom."
    },
    {
        "camera_set_viewport_position", (PyCFunction) PythonModules::camera_set_viewport_position,
        METH_VARARGS | METH_KEYWORDS, "Set viewport's position."
    },
    // NODE
    {
        "node_get_node", (PyCFunction) PythonModules::node_get_node,
        METH_VARARGS | METH_KEYWORDS, "Gets a node if name exists."
    },
    {
        "node_queue_deletion", (PyCFunction) PythonModules::node_queue_deletion,
        METH_VARARGS | METH_KEYWORDS, "Queues node for deletion."
    },
    // NODE2D
    {
        "node2D_get_position", (PyCFunction) PythonModules::node2D_get_position,
        METH_VARARGS | METH_KEYWORDS, "Gets a node's position."
    },
    {
        "node2D_set_position", (PyCFunction) PythonModules::node2D_set_position,
        METH_VARARGS | METH_KEYWORDS, "Sets a node's position."
    },
    {
        "node2D_add_to_position", (PyCFunction) PythonModules::node2D_add_to_position,
        METH_VARARGS | METH_KEYWORDS, "Adds to a node's position."
    },
    // TEXT_LABEL
    {
        "text_label_get_text", (PyCFunction) PythonModules::text_label_get_text,
        METH_VARARGS | METH_KEYWORDS, "Gets a node's text."
    },
    {
        "text_label_set_text", (PyCFunction) PythonModules::text_label_set_text,
        METH_VARARGS | METH_KEYWORDS, "Sets a node's text."
    },
    // COLLISION
    {
        "collision_check", (PyCFunction) PythonModules::collision_check,
        METH_VARARGS | METH_KEYWORDS, "Checks if entity collided with others."
    },
    {
        "collision_get_collided_nodes", (PyCFunction) PythonModules::collision_get_collided_nodes,
        METH_VARARGS | METH_KEYWORDS, "Gets nodes entity collided with."
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
    // SCENE
    {
        "scene_tree_change_scene", (PyCFunction) PythonModules::scene_tree_change_scene,
        METH_VARARGS | METH_KEYWORDS, "Changes to a new scene."
    },
    {
        "scene_tree_get_current_scene_node", PythonModules::scene_tree_get_current_scene_node,
        METH_VARARGS, "Gets current active scene node."
    },

    {nullptr, nullptr, 0,nullptr },
};

static struct PyModuleDef rollEngineAPIModDef = {
    PyModuleDef_HEAD_INIT, "roll_engine_api", nullptr, -1, rollApiMethods,
    nullptr, nullptr, nullptr, nullptr
};

static char *engineExitKWList[] = {"code", nullptr};

static char *audioPlayMusicKWList[] = {"music_id", nullptr};
static char *audioPlaySoundKWList[] = {"sound_id", nullptr};
static char *audioSetVolumeKWList[] = {"volume", nullptr};

static char *cameraVector2SetKWList[] = {"x", "y", nullptr};

static char *nodeGetEntityKWList[] = {"entity_id", nullptr};
static char *nodeGetNodeKWList[] = {"name", nullptr};

static char *node2DUpdatePositionKWList[] = {"entity_id", "x", "y", nullptr};

static char *textLabelSetTextKWList[] = {"entity_id", "text", nullptr};

static char *inputAddActionKWList[] = {"action_name", "value", nullptr};
static char *inputActionCheckKWList[] = {"action_name", nullptr};

static char *sceneTreeChangeSceneKWList[] = {"scene_path", nullptr};

static PyObject* PyInit_rollEngineAPI(void) {
    return PyModule_Create(&rollEngineAPIModDef);
}

#endif //PYTHON_MODULES_H
