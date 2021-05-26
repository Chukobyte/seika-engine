# Project Properties

Project properties define how the game will be configured before running.  An example of the file is found below:

### Format

```json
{
  "game_title": "Fighting Game Proto",
  "initial_scene": "scenes/init.json",
  "base_resolution": {
    "width": 800,
    "height": 600
  },
  "colliders_visible": true,
  "target_fps": 60,
  "assets": [
    {
      "type": "texture",
      "file_path": "assets/game_projects/fighter/assets/fighters/puncher/puncher_basic_sheet.png"
    },
    {
      "type": "font",
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

Base resolution of the game

`colliders_visible`

If true, will render a visible box for colliders.

`assets`

Textures, fonts, music, and sound effect assets are defined here.

`input_actions`

Key bindings are defined here.
