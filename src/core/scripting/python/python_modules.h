#ifndef PYTHON_MODULES_H
#define PYTHON_MODULES_H

#define PY_SSIZE_T_CLEAN

#include <Python.h>
#include <string>

class PythonModules {
  public:
    static PyObject* engine_exit(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* engine_get_fps(PyObject* self, PyObject* args);

    static PyObject* audio_play_music(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* audio_stop_music(PyObject* self, PyObject* args);
    static PyObject* audio_set_music_volume(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* audio_play_sound(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* audio_set_sound_volume(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* audio_set_all_volume(PyObject* self, PyObject* args, PyObject* kwargs);

    static PyObject* camera_get_zoom(PyObject* self, PyObject* args);
    static PyObject* camera_set_zoom(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* camera_get_viewport_position(PyObject* self, PyObject* args);
    static PyObject* camera_set_viewport_position(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* camera_get_offset(PyObject* self, PyObject* args);
    static PyObject* camera_set_offset(PyObject* self, PyObject* args, PyObject* kwargs);

    static PyObject* node_new(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* node_add_child(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* node_get_node(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* node_queue_deletion(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* node_signal_create(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* node_signal_connect(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* node_signal_emit(PyObject* self, PyObject* args, PyObject* kwargs);

    static PyObject* node2D_get_position(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* node2D_set_position(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* node2D_add_to_position(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* node2D_get_rotation(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* node2D_set_rotation(PyObject* self, PyObject* args, PyObject* kwargs);

    static PyObject* sprite_get_flip_h(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* sprite_set_flip_h(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* sprite_get_flip_v(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* sprite_set_flip_v(PyObject* self, PyObject* args, PyObject* kwargs);

    static PyObject* animated_sprite_play(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* animated_sprite_set_animation(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* animated_sprite_stop(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* animated_sprite_is_playing(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* animated_sprite_get_frame(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* animated_sprite_set_frame(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* animated_sprite_get_animation_frames(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* animated_sprite_get_animation_speed(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* animated_sprite_get_flip_h(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* animated_sprite_set_flip_h(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* animated_sprite_get_flip_v(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* animated_sprite_set_flip_v(PyObject* self, PyObject* args, PyObject* kwargs);

    static PyObject* text_label_get_text(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* text_label_set_text(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* text_label_get_color(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* text_label_set_color(PyObject* self, PyObject* args, PyObject* kwargs);

    static PyObject* collision_shape2d_get_collider_rect(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* collision_shape2d_set_collider_rect(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* collision_shape2d_add_collision_exception(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* collision_shape2d_remove_collision_exception(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* collision_shape2d_get_color(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* collision_shape2d_set_color(PyObject* self, PyObject* args, PyObject* kwargs);

    static PyObject* collision_get_collided_nodes(PyObject* self, PyObject* args, PyObject* kwargs);

    static PyObject* input_add_action(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* input_is_action_pressed(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* input_is_action_just_pressed(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* input_is_action_just_released(PyObject* self, PyObject* args, PyObject* kwargs);

    static PyObject* mouse_get_position(PyObject* self, PyObject* args);

    static PyObject* scene_tree_change_scene(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* scene_tree_get_current_scene_node(PyObject* self, PyObject* args);

    static PyObject* network_is_server(PyObject* self, PyObject* args);

    static PyObject* server_start(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* server_stop(PyObject* self, PyObject* args);
    static PyObject* server_send_message_to_all_clients(PyObject* self, PyObject* args, PyObject* kwargs);

    static PyObject* client_connect(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* client_disconnect(PyObject* self, PyObject* args);
    static PyObject* client_send_message_to_server(PyObject* self, PyObject* args, PyObject* kwargs);
};

static struct PyMethodDef rollApiMethods[] = {
    // ENGINE
    {
        "engine_exit", (PyCFunction) PythonModules::engine_exit,
        METH_VARARGS | METH_KEYWORDS, "Exits the engine."
    },
    {
        "engine_get_fps", PythonModules::engine_get_fps,
        METH_VARARGS, "Get FPS."
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
        "camera_get_zoom", PythonModules::camera_get_zoom,
        METH_VARARGS, "Get camera's zoom."
    },
    {
        "camera_set_zoom", (PyCFunction) PythonModules::camera_set_zoom,
        METH_VARARGS | METH_KEYWORDS, "Set camera's zoom."
    },
    {
        "camera_get_viewport_position", PythonModules::camera_get_viewport_position,
        METH_VARARGS, "Get viewport's position."
    },
    {
        "camera_set_viewport_position", (PyCFunction) PythonModules::camera_set_viewport_position,
        METH_VARARGS | METH_KEYWORDS, "Set viewport's position."
    },
    {
        "camera_get_offset", PythonModules::camera_get_offset,
        METH_VARARGS, "Get camera's offset."
    },
    {
        "camera_set_offset", (PyCFunction) PythonModules::camera_set_offset,
        METH_VARARGS | METH_KEYWORDS, "Set camera's offset."
    },
    // NODE
    {
        "node_new", (PyCFunction) PythonModules::node_new,
        METH_VARARGS | METH_KEYWORDS, "Creates new node."
    },
    {
        "node_add_child", (PyCFunction) PythonModules::node_add_child,
        METH_VARARGS | METH_KEYWORDS, "Adds a child to a parent node."
    },
    {
        "node_get_node", (PyCFunction) PythonModules::node_get_node,
        METH_VARARGS | METH_KEYWORDS, "Gets a node if name exists."
    },
    {
        "node_queue_deletion", (PyCFunction) PythonModules::node_queue_deletion,
        METH_VARARGS | METH_KEYWORDS, "Queues node for deletion."
    },
    {
        "node_signal_create", (PyCFunction) PythonModules::node_signal_create,
        METH_VARARGS | METH_KEYWORDS, "Creates a signal."
    },
    {
        "node_signal_connect", (PyCFunction) PythonModules::node_signal_connect,
        METH_VARARGS | METH_KEYWORDS, "Connects to a signal."
    },
    {
        "node_signal_emit", (PyCFunction) PythonModules::node_signal_emit,
        METH_VARARGS | METH_KEYWORDS, "Emits a signal."
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
    {
        "node2D_get_rotation", (PyCFunction) PythonModules::node2D_get_rotation,
        METH_VARARGS | METH_KEYWORDS, "Gets a node's rotation."
    },
    {
        "node2D_set_rotation", (PyCFunction) PythonModules::node2D_set_rotation,
        METH_VARARGS | METH_KEYWORDS, "Sets a node's rotation."
    },
    // SPRITE
    {
        "sprite_get_flip_h", (PyCFunction) PythonModules::sprite_get_flip_h,
        METH_VARARGS | METH_KEYWORDS, "Gets a sprite's flip h."
    },
    {
        "sprite_set_flip_h", (PyCFunction) PythonModules::sprite_set_flip_h,
        METH_VARARGS | METH_KEYWORDS, "Sets a sprite's flip h."
    },
    {
        "sprite_get_flip_v", (PyCFunction) PythonModules::sprite_get_flip_v,
        METH_VARARGS | METH_KEYWORDS, "Gets a sprite's flip v."
    },
    {
        "sprite_set_flip_v", (PyCFunction) PythonModules::sprite_set_flip_v,
        METH_VARARGS | METH_KEYWORDS, "Sets a sprite's flip v."
    },
    // ANIMATED_SPRITE
    {
        "animated_sprite_play", (PyCFunction) PythonModules::animated_sprite_play,
        METH_VARARGS | METH_KEYWORDS, "Plays animation."
    },
    {
        "animated_sprite_set_animation", (PyCFunction) PythonModules::animated_sprite_set_animation,
        METH_VARARGS | METH_KEYWORDS, "Set sprite animation."
    },
    {
        "animated_sprite_stop", (PyCFunction) PythonModules::animated_sprite_stop,
        METH_VARARGS | METH_KEYWORDS, "Stops animation."
    },
    {
        "animated_sprite_is_playing", (PyCFunction) PythonModules::animated_sprite_is_playing,
        METH_VARARGS | METH_KEYWORDS, "Returns if an animations is playing."
    },
    {
        "animated_sprite_get_frame", (PyCFunction) PythonModules::animated_sprite_get_frame,
        METH_VARARGS | METH_KEYWORDS, "Returns frame of current playing animation."
    },
    {
        "animated_sprite_set_frame", (PyCFunction) PythonModules::animated_sprite_set_frame,
        METH_VARARGS | METH_KEYWORDS, "Sets the frame of the current playing animation."
    },
    {
        "animated_sprite_get_animation_frames", (PyCFunction) PythonModules::animated_sprite_get_animation_frames,
        METH_VARARGS | METH_KEYWORDS, "Returns total frame count of current playing animation."
    },
    {
        "animated_sprite_get_animation_speed", (PyCFunction) PythonModules::animated_sprite_get_animation_speed,
        METH_VARARGS | METH_KEYWORDS, "Returns speed current playing animation in frames per milliseconds."
    },
    {
        "animated_sprite_get_flip_h", (PyCFunction) PythonModules::animated_sprite_get_flip_h,
        METH_VARARGS | METH_KEYWORDS, "Gets a sprite's flip h."
    },
    {
        "animated_sprite_set_flip_h", (PyCFunction) PythonModules::animated_sprite_set_flip_h,
        METH_VARARGS | METH_KEYWORDS, "Sets a sprite's flip h."
    },
    {
        "animated_sprite_get_flip_v", (PyCFunction) PythonModules::animated_sprite_get_flip_v,
        METH_VARARGS | METH_KEYWORDS, "Gets a sprite's flip v."
    },
    {
        "animated_sprite_set_flip_v", (PyCFunction) PythonModules::animated_sprite_set_flip_v,
        METH_VARARGS | METH_KEYWORDS, "Sets a sprite's flip v."
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
    {
        "text_label_get_color", (PyCFunction) PythonModules::text_label_get_color,
        METH_VARARGS | METH_KEYWORDS, "Gets a text label's color."
    },
    {
        "text_label_set_color", (PyCFunction) PythonModules::text_label_set_color,
        METH_VARARGS | METH_KEYWORDS, "Sets a text label's color."
    },
    // COLLISION SHAPE2D
    {
        "collision_shape2d_get_collider_rect", (PyCFunction) PythonModules::collision_shape2d_get_collider_rect,
        METH_VARARGS | METH_KEYWORDS, "Get collider's rectangle."
    },
    {
        "collision_shape2d_set_collider_rect", (PyCFunction) PythonModules::collision_shape2d_set_collider_rect,
        METH_VARARGS | METH_KEYWORDS, "Set collider's rectangle."
    },
    {
        "collision_shape2d_get_color", (PyCFunction) PythonModules::collision_shape2d_get_color,
        METH_VARARGS | METH_KEYWORDS, "Gets a collider's color."
    },
    {
        "collision_shape2d_set_color", (PyCFunction) PythonModules::collision_shape2d_set_color,
        METH_VARARGS | METH_KEYWORDS, "Sets a collider's color."
    },
    // COLLISION
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
    {
        "mouse_get_position", PythonModules::mouse_get_position,
        METH_VARARGS, "Gets mouse's position."
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
    // NETWORK
    {
        "network_is_server", PythonModules::network_is_server,
        METH_VARARGS, "Checks if network is initialized as a server."
    },
    // SERVER
    {
        "server_start", (PyCFunction) PythonModules::server_start,
        METH_VARARGS | METH_KEYWORDS, "Starts a server."
    },
    {
        "server_stop", PythonModules::server_stop,
        METH_VARARGS, "Stops a server."
    },
    {
        "server_send_message_to_all_clients", (PyCFunction) PythonModules::server_send_message_to_all_clients,
        METH_VARARGS | METH_KEYWORDS, "Sends a message through the network to all clients."
    },
    // CLIENT
    {
        "client_connect", (PyCFunction) PythonModules::client_connect,
        METH_VARARGS | METH_KEYWORDS, "Connects a client to an endpoint."
    },
    {
        "client_disconnect", PythonModules::client_disconnect,
        METH_VARARGS, "Disconnects a client from an endpoint."
    },
    {
        "client_send_message_to_server", (PyCFunction) PythonModules::client_send_message_to_server,
        METH_VARARGS | METH_KEYWORDS, "Sends a message through the network to the server."
    },

    {nullptr, nullptr, 0,nullptr },
};

static struct PyModuleDef seikaEngineAPIModDef = {
    PyModuleDef_HEAD_INIT, "seika_engine_api", nullptr, -1, rollApiMethods,
    nullptr, nullptr, nullptr, nullptr
};

static char *engineExitKWList[] = {"code", nullptr};

static char *audioPlayMusicKWList[] = {"music_id", nullptr};
static char *audioPlaySoundKWList[] = {"sound_id", nullptr};
static char *audioSetVolumeKWList[] = {"volume", nullptr};

static char *cameraVector2SetKWList[] = {"x", "y", nullptr};

static char *nodeGetEntityKWList[] = {"entity_id", nullptr};
static char *nodeNewKWList[] = {"class_path", "class_name", "node_type", nullptr};
static char *nodeAddChildKWList[] = {"parent_entity_id", "child_entity_id", nullptr};
static char *nodeGetNodeKWList[] = {"name", nullptr};
static char *nodeSignalCreateKWList[] = {"entity_id", "signal_id", nullptr};
static char *nodeSignalConnectKWList[] = {"entity_id", "signal_id", "listener_entity_id", "function_name", nullptr};
static char *nodeSignalEmitKWList[] = {"entity_id", "signal_id", "args", nullptr};

static char *nodeSetColorKWList[] = {"entity_id", "red", "green", "blue", "alpha", nullptr};

static char *node2DUpdatePositionKWList[] = {"entity_id", "x", "y", nullptr};
static char *node2DSetRotationKWList[] = {"entity_id", "rotation", nullptr};

static char *setSpriteFlipHKWList[] = {"entity_id", "flip_h", nullptr};
static char *setSpriteFlipVKWList[] = {"entity_id", "flip_v", nullptr};

static char *animatedSpriteAnimationUpdateKWList[] = {"entity_id", "animation_name", nullptr};
static char *animatedSpriteSetFrameKWList[] = {"entity_id", "frame", nullptr};

static char *textLabelSetTextKWList[] = {"entity_id", "text", nullptr};

static char *collisionShape2DSetColliderRectKWList[] = {"entity_id", "x", "y", "w", "h", nullptr};
static char *collisionModifyCollisionExceptionKWList[] = {"entity_id", "exception_entity_id", nullptr};

static char *inputAddActionKWList[] = {"action_name", "value", nullptr};
static char *inputActionCheckKWList[] = {"action_name", nullptr};

static char *sceneTreeChangeSceneKWList[] = {"scene_path", nullptr};

static char *serverStartKWList[] = {"port", nullptr};

static char *clientConnectKWList[] = {"endpoint", "port", nullptr};

static char *networkSendMessageKWList[] = {"message", nullptr};

static PyObject* PyInit_seikaEngineAPI(void) {
    return PyModule_Create(&seikaEngineAPIModDef);
}

#endif //PYTHON_MODULES_H
