# Project Properties

Project properties define how the game will be configured before running.  An example of the file is found below:

### Format

```json
{
  "game_title": "Fighting Game Proto",
  "initial_scene": "scenes/init.sscn",
  "base_resolution": {
    "width": 800,
    "height": 600
  },
  "window_size": {
    "width": 800,
    "height": 600
  },
  "colliders_visible": true,
  "pixel_snap": true,
  "target_fps": 60,
  "background_color": {
    "red": 0.1,
    "green": 0.1,
    "blue": 0.1
  },
  "assets": [
    {
      "type": "texture",
      "file_path": "assets/fighters/puncher/puncher_basic_sheet.png",
      "wrap_s": "clamp_to_border",
      "wrap_t": "clamp_to_border",
      "filter_min": "nearest",
      "filter_max": "nearest"
    },
    {
      "type": "font",
      "uid": "bruh",
      "file_path": "assets/fonts/bruh.ttf",
      "size": 60
    },
    {
      "type": "music",
      "file_path": "assets/audio/music/test_music.wav"
    },
    {
      "type": "sound",
      "file_path": "assets/audio/sound/test_sound_effect.wav"
    },
    {
      "type": "audio-stream",
      "file_path": "assets/audio/music/test_music.wav",
      "uid": "test-song",
      "pitch": 1.0,
      "gain": 1.0,
      "loops": true
    }
  ],
  "input_actions": [
    {
      "name": "quit",
      "values": ["esc"]
    },
    {
      "name": "confirm",
      "values": ["return"]
    }
  ]
}
```

### Properties

`game_title`

Title of the game window.

`initial_scene`

First scene loaded for the game.

`base_resolution`

Base resolution of the game.

`window_size`

The initial window size when starting the game.

`colliders_visible`

If true, will render a visible box for colliders.

`pixel_snap`

If true, will snap all entity render positions to a grid.

`target_fps`

The FPS that the current game tries to achieve.

`background_color`

The background draw color of the renderer.

`assets`

Textures, fonts, music, and sound effect assets are defined here.

`input_actions`

Key bindings are defined here.
