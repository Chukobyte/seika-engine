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

    static PyObject* audio_stream_get(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* audio_stream_set_pitch(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* audio_stream_set_gain(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* audio_stream_set_loops(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* audio_stream_play(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* audio_stream_stop(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* audio_stream_is_playing(PyObject* self, PyObject* args, PyObject* kwargs);

    static PyObject* camera2d_get_zoom(PyObject* self, PyObject* args);
    static PyObject* camera2d_set_zoom(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* camera2d_get_viewport_position(PyObject* self, PyObject* args);
    static PyObject* camera2d_set_viewport_position(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* camera2d_get_offset(PyObject* self, PyObject* args);
    static PyObject* camera2d_set_offset(PyObject* self, PyObject* args, PyObject* kwargs);

    static PyObject* camera3d_move_left(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* camera3d_move_right(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* camera3d_move_up(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* camera3d_move_down(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* camera3d_add_yaw(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* camera3d_add_pitch(PyObject* self, PyObject* args, PyObject* kwargs);

    static PyObject* node_new(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* node_add_child(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* node_get_node(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* node_queue_deletion(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* node_signal_create(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* node_signal_connect(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* node_signal_emit(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* node_get_name(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* node_get_tags(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* node_set_tags(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* node_show(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* node_hide(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* node_is_visible(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* node_get_parent(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* node_get_children(PyObject* self, PyObject* args, PyObject* kwargs);

    static PyObject* timer_start(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* timer_stop(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* timer_pause(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* timer_resume(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* timer_get_wait_time(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* timer_set_wait_time(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* timer_get_time_left(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* timer_is_stopped(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* timer_is_paused(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* timer_get_loops(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* timer_set_loops(PyObject* self, PyObject* args, PyObject* kwargs);

    static PyObject* node2D_get_position(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* node2D_set_position(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* node2D_add_to_position(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* node2D_get_rotation(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* node2D_set_rotation(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* node2D_get_z_index(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* node2D_set_z_index(PyObject* self, PyObject* args, PyObject* kwargs);

    static PyObject* sprite_get_flip_h(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* sprite_set_flip_h(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* sprite_get_flip_v(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* sprite_set_flip_v(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* sprite_get_modulate(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* sprite_set_modulate(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* sprite_get_texture(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* sprite_set_texture(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* sprite_get_draw_source(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* sprite_set_draw_source(PyObject* self, PyObject* args, PyObject* kwargs);

    static PyObject* animated_sprite_play(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* animated_sprite_set_animation(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* animated_sprite_stop(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* animated_sprite_get_animations(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* animated_sprite_set_animations(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* animated_sprite_get_loops(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* animated_sprite_set_loops(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* animated_sprite_is_playing(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* animated_sprite_get_modulate(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* animated_sprite_set_modulate(PyObject* self, PyObject* args, PyObject* kwargs);
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
    static PyObject* text_label_get_font(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* text_label_set_font(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* text_label_get_word_wrap(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* text_label_set_word_wrap(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* text_label_get_max_characters_per_line(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* text_label_set_max_characters_per_line(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* text_label_get_new_line_padding(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* text_label_set_new_line_padding(PyObject* self, PyObject* args, PyObject* kwargs);

    static PyObject* collision_shape2d_get_collider_rect(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* collision_shape2d_set_collider_rect(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* collision_shape2d_add_collision_exception(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* collision_shape2d_remove_collision_exception(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* collision_shape2d_get_color(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* collision_shape2d_set_color(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* collision_shape2d_is_under_mouse(PyObject* self, PyObject* args, PyObject* kwargs);

    static PyObject* collision_get_collided_nodes(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* collision_get_collided_nodes_by_tag(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* collision_update_collisions(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* collision_get_nodes_under_mouse(PyObject* self, PyObject* args);

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

    static PyObject* renderer_draw_texture(PyObject* self, PyObject* args, PyObject* kwargs);

    static PyObject* texture_get(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* texture_get_pixel_color(PyObject* self, PyObject* args, PyObject* kwargs);

    static PyObject* font_create(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* font_get(PyObject* self, PyObject* args, PyObject* kwargs);

    static PyObject* config_tool_save_file(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* config_tool_load_file(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* config_tool_delete_file(PyObject* self, PyObject* args, PyObject* kwargs);
    static PyObject* config_tool_does_file_exist(PyObject* self, PyObject* args, PyObject* kwargs);
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
    // AUDIO STREAM
    {
        "audio_stream_get", (PyCFunction) PythonModules::audio_stream_get,
        METH_VARARGS | METH_KEYWORDS, "Get data for an audio stream."
    },
    {
        "audio_stream_set_pitch", (PyCFunction) PythonModules::audio_stream_set_pitch,
        METH_VARARGS | METH_KEYWORDS, "Sets the pitch for an audio stream."
    },
    {
        "audio_stream_set_gain", (PyCFunction) PythonModules::audio_stream_set_gain,
        METH_VARARGS | METH_KEYWORDS, "Sets the gain for an audio stream."
    },
    {
        "audio_stream_set_loops", (PyCFunction) PythonModules::audio_stream_set_loops,
        METH_VARARGS | METH_KEYWORDS, "Sets if an audio stream loops when reaching the end."
    },
    {
        "audio_stream_play", (PyCFunction) PythonModules::audio_stream_play,
        METH_VARARGS | METH_KEYWORDS, "Plays an audio stream."
    },
    {
        "audio_stream_stop", (PyCFunction) PythonModules::audio_stream_stop,
        METH_VARARGS | METH_KEYWORDS, "Stops an audio stream."
    },
    {
        "audio_stream_is_playing", (PyCFunction) PythonModules::audio_stream_is_playing,
        METH_VARARGS | METH_KEYWORDS, "Returns if an audio stream is playing."
    },
    // CAMERA 2D
    {
        "camera2d_get_zoom", PythonModules::camera2d_get_zoom,
        METH_VARARGS, "Get camera's zoom."
    },
    {
        "camera2d_set_zoom", (PyCFunction) PythonModules::camera2d_set_zoom,
        METH_VARARGS | METH_KEYWORDS, "Set camera's zoom."
    },
    {
        "camera2d_get_viewport_position", PythonModules::camera2d_get_viewport_position,
        METH_VARARGS, "Get viewport's position."
    },
    {
        "camera2d_set_viewport_position", (PyCFunction) PythonModules::camera2d_set_viewport_position,
        METH_VARARGS | METH_KEYWORDS, "Set viewport's position."
    },
    {
        "camera2d_get_offset", PythonModules::camera2d_get_offset,
        METH_VARARGS, "Get camera's offset."
    },
    {
        "camera2d_set_offset", (PyCFunction) PythonModules::camera2d_set_offset,
        METH_VARARGS | METH_KEYWORDS, "Set camera's offset."
    },
    // CAMERA 3D
    {
        "camera3d_move_left", (PyCFunction) PythonModules::camera3d_move_left,
        METH_VARARGS | METH_KEYWORDS, "Move camera left."
    },
    {
        "camera3d_move_right", (PyCFunction) PythonModules::camera3d_move_right,
        METH_VARARGS | METH_KEYWORDS, "Move camera right."
    },
    {
        "camera3d_move_up", (PyCFunction) PythonModules::camera3d_move_up,
        METH_VARARGS | METH_KEYWORDS, "Move camera up."
    },
    {
        "camera3d_move_down", (PyCFunction) PythonModules::camera3d_move_down,
        METH_VARARGS | METH_KEYWORDS, "Move camera down."
    },
    {
        "camera3d_add_yaw", (PyCFunction) PythonModules::camera3d_add_yaw,
        METH_VARARGS | METH_KEYWORDS, "Add yaw to camera."
    },
    {
        "camera3d_add_pitch", (PyCFunction) PythonModules::camera3d_add_pitch,
        METH_VARARGS | METH_KEYWORDS, "Add pitch to camera."
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
    {
        "node_get_name", (PyCFunction) PythonModules::node_get_name,
        METH_VARARGS | METH_KEYWORDS, "Gets a node's unique name."
    },
    {
        "node_get_tags", (PyCFunction) PythonModules::node_get_tags,
        METH_VARARGS | METH_KEYWORDS, "Gets a node's tags."
    },
    {
        "node_set_tags", (PyCFunction) PythonModules::node_set_tags,
        METH_VARARGS | METH_KEYWORDS, "Sets a node's tags."
    },
    {
        "node_show", (PyCFunction) PythonModules::node_show,
        METH_VARARGS | METH_KEYWORDS, "Show a node."
    },
    {
        "node_hide", (PyCFunction) PythonModules::node_hide,
        METH_VARARGS | METH_KEYWORDS, "Hides a node."
    },
    {
        "node_is_visible", (PyCFunction) PythonModules::node_is_visible,
        METH_VARARGS | METH_KEYWORDS, "Returns if a node is visible."
    },
    {
        "node_get_parent", (PyCFunction) PythonModules::node_get_parent,
        METH_VARARGS | METH_KEYWORDS, "Returns parent node."
    },
    {
        "node_get_children", (PyCFunction) PythonModules::node_get_children,
        METH_VARARGS | METH_KEYWORDS, "Returns a node's children."
    },
    // TIMER
    {
        "timer_start", (PyCFunction) PythonModules::timer_start,
        METH_VARARGS | METH_KEYWORDS, "Starts timer."
    },
    {
        "timer_stop", (PyCFunction) PythonModules::timer_stop,
        METH_VARARGS | METH_KEYWORDS, "Stops timer."
    },
    {
        "timer_pause", (PyCFunction) PythonModules::timer_pause,
        METH_VARARGS | METH_KEYWORDS, "Pauses timer."
    },
    {
        "timer_resume", (PyCFunction) PythonModules::timer_resume,
        METH_VARARGS | METH_KEYWORDS, "Resumes timer."
    },
    {
        "timer_get_wait_time", (PyCFunction) PythonModules::timer_get_wait_time,
        METH_VARARGS | METH_KEYWORDS, "Returns timer's wait time."
    },
    {
        "timer_set_wait_time", (PyCFunction) PythonModules::timer_set_wait_time,
        METH_VARARGS | METH_KEYWORDS, "Sets timer's wait time."
    },
    {
        "timer_get_time_left", (PyCFunction) PythonModules::timer_get_time_left,
        METH_VARARGS | METH_KEYWORDS, "Returns timer's time left."
    },
    {
        "timer_is_stopped", (PyCFunction) PythonModules::timer_is_stopped,
        METH_VARARGS | METH_KEYWORDS, "Checks if a timer is stopped."
    },
    {
        "timer_is_paused", (PyCFunction) PythonModules::timer_is_paused,
        METH_VARARGS | METH_KEYWORDS, "Checks if a timer is paused."
    },
    {
        "timer_get_loops", (PyCFunction) PythonModules::timer_get_loops,
        METH_VARARGS | METH_KEYWORDS, "Checks if a timer loops."
    },
    {
        "timer_set_loops", (PyCFunction) PythonModules::timer_set_loops,
        METH_VARARGS | METH_KEYWORDS, "Makes a timer loop."
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
    {
        "node2D_get_z_index", (PyCFunction) PythonModules::node2D_get_z_index,
        METH_VARARGS | METH_KEYWORDS, "Returns a node's z_index."
    },
    {
        "node2D_set_z_index", (PyCFunction) PythonModules::node2D_set_z_index,
        METH_VARARGS | METH_KEYWORDS, "Sets a node's z_index."
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
    {
        "sprite_get_modulate", (PyCFunction) PythonModules::sprite_get_modulate,
        METH_VARARGS | METH_KEYWORDS, "Gets a sprite's color."
    },
    {
        "sprite_set_modulate", (PyCFunction) PythonModules::sprite_set_modulate,
        METH_VARARGS | METH_KEYWORDS, "Sets a sprite's color."
    },
    {
        "sprite_get_texture", (PyCFunction) PythonModules::sprite_get_texture,
        METH_VARARGS | METH_KEYWORDS, "Gets a sprite's texture."
    },
    {
        "sprite_set_texture", (PyCFunction) PythonModules::sprite_set_texture,
        METH_VARARGS | METH_KEYWORDS, "Sets a sprite's texture."
    },
    {
        "sprite_get_draw_source", (PyCFunction) PythonModules::sprite_get_draw_source,
        METH_VARARGS | METH_KEYWORDS, "Gets a sprite's draw source."
    },
    {
        "sprite_set_draw_source", (PyCFunction) PythonModules::sprite_set_draw_source,
        METH_VARARGS | METH_KEYWORDS, "Sets a sprite's draw source."
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
        "animated_sprite_get_animations", (PyCFunction) PythonModules::animated_sprite_get_animations,
        METH_VARARGS | METH_KEYWORDS, "Gets all entity's animations."
    },
    {
        "animated_sprite_set_animations", (PyCFunction) PythonModules::animated_sprite_set_animations,
        METH_VARARGS | METH_KEYWORDS, "Sets all animations for entity."
    },
    {
        "animated_sprite_get_loops", (PyCFunction) PythonModules::animated_sprite_get_loops,
        METH_VARARGS | METH_KEYWORDS, "Returns is an animated sprite loops its animation."
    },
    {
        "animated_sprite_set_loops", (PyCFunction) PythonModules::animated_sprite_set_loops,
        METH_VARARGS | METH_KEYWORDS, "Sets if an animated sprite loops its animation."
    },
    {
        "animated_sprite_is_playing", (PyCFunction) PythonModules::animated_sprite_is_playing,
        METH_VARARGS | METH_KEYWORDS, "Returns if an animations is playing."
    },
    {
        "animated_sprite_get_modulate", (PyCFunction) PythonModules::animated_sprite_get_modulate,
        METH_VARARGS | METH_KEYWORDS, "Gets an animated sprite's color."
    },
    {
        "animated_sprite_set_modulate", (PyCFunction) PythonModules::animated_sprite_set_modulate,
        METH_VARARGS | METH_KEYWORDS, "Sets an animated sprite's color."
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
    {
        "text_label_get_font", (PyCFunction) PythonModules::text_label_get_font,
        METH_VARARGS | METH_KEYWORDS, "Gets a text label's font."
    },
    {
        "text_label_set_font", (PyCFunction) PythonModules::text_label_set_font,
        METH_VARARGS | METH_KEYWORDS, "Sets a text label's font."
    },
    {
        "text_label_get_word_wrap", (PyCFunction) PythonModules::text_label_get_word_wrap,
        METH_VARARGS | METH_KEYWORDS, "Gets whether a text label has word wrapping enabled."
    },
    {
        "text_label_set_word_wrap", (PyCFunction) PythonModules::text_label_set_word_wrap,
        METH_VARARGS | METH_KEYWORDS, "Sets whether a text label has word wrapping enabled."
    },
    {
        "text_label_get_max_characters_per_line", (PyCFunction) PythonModules::text_label_get_max_characters_per_line,
        METH_VARARGS | METH_KEYWORDS, "Gets max characters allowed for a line."
    },
    {
        "text_label_set_max_characters_per_line", (PyCFunction) PythonModules::text_label_set_max_characters_per_line,
        METH_VARARGS | METH_KEYWORDS, "Sets max characters allowed for a line."
    },
    {
        "text_label_get_new_line_padding", (PyCFunction) PythonModules::text_label_get_new_line_padding,
        METH_VARARGS | METH_KEYWORDS, "Gets new line padding for text label."
    },
    {
        "text_label_set_new_line_padding", (PyCFunction) PythonModules::text_label_set_new_line_padding,
        METH_VARARGS | METH_KEYWORDS, "Sets new line padding for text label."
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
    {
        "collision_shape2d_is_under_mouse", (PyCFunction) PythonModules::collision_shape2d_is_under_mouse,
        METH_VARARGS | METH_KEYWORDS, "Checks if collision shape 2D is under mouse cursor."
    },
    // COLLISION
    {
        "collision_get_collided_nodes", (PyCFunction) PythonModules::collision_get_collided_nodes,
        METH_VARARGS | METH_KEYWORDS, "Gets nodes entity collided with."
    },
    {
        "collision_get_collided_nodes_by_tag", (PyCFunction) PythonModules::collision_get_collided_nodes_by_tag,
        METH_VARARGS | METH_KEYWORDS, "Gets nodes entity collided with by tag."
    },
    {
        "collision_update_collisions", (PyCFunction) PythonModules::collision_update_collisions,
        METH_VARARGS | METH_KEYWORDS, "Forces an update of collision data."
    },
    {
        "collision_get_nodes_under_mouse", PythonModules::collision_get_nodes_under_mouse,
        METH_VARARGS, "Gets nodes mouse is hovering over."
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
    // RENDERER
    {
        "renderer_draw_texture", (PyCFunction) PythonModules::renderer_draw_texture,
        METH_VARARGS | METH_KEYWORDS, "Renders a texture."
    },
    // TEXTURE
    {
        "texture_get", (PyCFunction) PythonModules::texture_get,
        METH_VARARGS | METH_KEYWORDS, "Gets a texture by path."
    },
    {
        "texture_get_pixel_color", (PyCFunction) PythonModules::texture_get_pixel_color,
        METH_VARARGS | METH_KEYWORDS, "Gets a texture's pixel color by coordinates."
    },
    // FONT
    {
        "font_create", (PyCFunction) PythonModules::font_create,
        METH_VARARGS | METH_KEYWORDS, "Creates a new font in memory."
    },
    {
        "font_get", (PyCFunction) PythonModules::font_get,
        METH_VARARGS | METH_KEYWORDS, "Gets an already existing font."
    },
    // CONFIG_TOOL
    {
        "config_tool_save_file", (PyCFunction) PythonModules::config_tool_save_file,
        METH_VARARGS | METH_KEYWORDS, "Saves a file."
    },
    {
        "config_tool_load_file", (PyCFunction) PythonModules::config_tool_load_file,
        METH_VARARGS | METH_KEYWORDS, "Loads a file."
    },
    {
        "config_tool_delete_file", (PyCFunction) PythonModules::config_tool_delete_file,
        METH_VARARGS | METH_KEYWORDS, "Deletes a file."
    },
    {
        "config_tool_does_file_exist", (PyCFunction) PythonModules::config_tool_does_file_exist,
        METH_VARARGS | METH_KEYWORDS, "Checks if a file exists."
    },

    {nullptr, nullptr, 0,nullptr },
};

static struct PyModuleDef seikaEngineAPIModDef = {
    PyModuleDef_HEAD_INIT, "seika_engine_api", nullptr, -1, rollApiMethods,
    nullptr, nullptr, nullptr, nullptr
};

static char *engineExitKWList[] = {"code", nullptr};

static char *audioPlayMusicKWList[] = {"music_id", "loops", nullptr};
static char *audioPlaySoundKWList[] = {"sound_id", nullptr};
static char *audioSetVolumeKWList[] = {"volume", nullptr};

static char *audioStreamGetKWList[] = {"uid", nullptr};
static char *audioStreamSetPitchKWList[] = {"uid", "pitch", nullptr};
static char *audioStreamSetGainKWList[] = {"uid", "gain", nullptr};
static char *audioStreamSetLoopsKWList[] = {"uid", "loops", nullptr};

static char *camera2dVector2SetKWList[] = {"x", "y", nullptr};

static char *camera3dMoveKWList[] = {"speed", nullptr};
static char *camera3dAddYawKWList[] = {"yaw", nullptr};
static char *camera3dAddPitchKWList[] = {"pitch", nullptr};

static char *nodeGetEntityKWList[] = {"entity_id", nullptr};
static char *nodeNewKWList[] = {"class_path", "class_name", "node_type", nullptr};
static char *nodeAddChildKWList[] = {"parent_entity_id", "child_entity_id", nullptr};
static char *nodeGetNodeKWList[] = {"name", nullptr};
static char *nodeSignalCreateKWList[] = {"entity_id", "signal_id", nullptr};
static char *nodeSignalConnectKWList[] = {"entity_id", "signal_id", "listener_entity_id", "function_name", nullptr};
static char *nodeSignalEmitKWList[] = {"entity_id", "signal_id", "args", nullptr};
static char *nodeSetTagsKWList[] = {"entity_id", "tags", nullptr};

static char *nodeSetColorKWList[] = {"entity_id", "red", "green", "blue", "alpha", nullptr};

static char *timerSetWaitTimeKWList[] = {"entity_id", "wait_time", nullptr};
static char *timerSetLoopsKWList[] = {"entity_id", "loops", nullptr};

static char *node2DUpdatePositionKWList[] = {"entity_id", "x", "y", nullptr};
static char *node2DSetRotationKWList[] = {"entity_id", "rotation", nullptr};
static char *node2DSetZIndexKWList[] = {"entity_id", "z_index", nullptr};

static char *spriteSetSpriteFlipHKWList[] = {"entity_id", "flip_h", nullptr};
static char *spriteSetSpriteFlipVKWList[] = {"entity_id", "flip_v", nullptr};
static char *spriteSetTextureKWList[] = {"entity_id", "file_path", nullptr};
static char *spriteSetDrawSourceKWList[] = {"entity_id", "x", "y", "w", "h", nullptr};

static char *animatedSpriteAnimationUpdateKWList[] = {"entity_id", "animation_name", nullptr};
static char *animatedSpriteSetAnimationsKWList[] = {"entity_id", "animations", nullptr};
static char *animatedSpriteSetLoopsKWList[] = {"entity_id", "loops", nullptr};
static char *animatedSpriteSetFrameKWList[] = {"entity_id", "frame", nullptr};

static char *textLabelSetTextKWList[] = {"entity_id", "text", nullptr};
static char *textLabelSetFontKWList[] = {"entity_id", "uid", nullptr};
static char *textLabelSetWordWrapKWList[] = {"entity_id", "word_wrap", nullptr};
static char *textLabelSetMaxCharactersPerLineKWList[] = {"entity_id", "max_characters", nullptr};
static char *textLabelSetNewLinePaddingKWList[] = {"entity_id", "new_line_padding", nullptr};

static char *collisionShape2DSetColliderRectKWList[] = {"entity_id", "x", "y", "w", "h", nullptr};
static char *collisionModifyCollisionExceptionKWList[] = {"entity_id", "exception_entity_id", nullptr};

static char *collisionUpdateCollisionsKWList[] = {"entity_id", "offset_x", "offset_y", nullptr};
static char *collisionGetCollidedNodesByTagKWList[] = {"entity_id", "tag", "offset_x", "offset_y", nullptr};

static char *inputAddActionKWList[] = {"action_name", "value", nullptr};
static char *inputActionCheckKWList[] = {"action_name", nullptr};

static char *sceneTreeChangeSceneKWList[] = {"scene_path", nullptr};

static char *serverStartKWList[] = {"port", nullptr};

static char *clientConnectKWList[] = {"endpoint", "port", nullptr};

static char *networkSendMessageKWList[] = {"message", nullptr};

static char *rendererDrawTextureKWList[] = {"texture_path",
                                            "source_rect_x", "source_rect_y", "source_rect_w", "source_rect_h",
                                            "dest_rect_x", "dest_rect_y", "dest_rect_w", "dest_rect_h",
                                            "z_index", "rotation",
                                            "color_red", "color_green", "color_blue", "color_alpha",
                                            "flip_x", "flip_y",
                                            nullptr
                                           };

static char *textureGetKWList[] = {"file_path", nullptr};
static char *textureGetPixelColorKWList[] = {"file_path", "x", "y", nullptr};

static char *fontCreateKWList[] = {"uid", "file_path", "size", nullptr};
static char *fontGetKWList[] = {"uid", nullptr};

static char *configToolSaveFileKWList[] = {"file_path", "json_data", "encryption_key", nullptr};
static char *configToolLoadFileKWList[] = {"file_path", "encryption_key", nullptr};
static char *configToolGetFileKWList[] = {"file_path", nullptr};

static PyObject* PyInit_seikaEngineAPI(void) {
    return PyModule_Create(&seikaEngineAPIModDef);
}

#endif //PYTHON_MODULES_H
