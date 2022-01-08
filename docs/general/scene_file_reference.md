# Scene File Reference

## About

A reference to how scene nodes are serialized in json.  The editor configures these files for the engine to read.

## Node Types

### Node

```json
{
    "name": "Node Example",
    "type": "Node",
    "tags": [],
    "external_scene_source": "",
    "components": [],
    "children": []
}
```

---

### Timer

```json
{
    "name": "Timer Example",
    "type": "Timer",
    "tags": [],
    "external_scene_source": "",
    "components": [
      {
        "timer": {
          "wait_time": 1.0,
          "loops": true
        }
      }
    ],
    "children": []
}
```

---

### Node2D

```json
{
    "name": "Node2D Example",
    "type": "Node2D",
    "tags": [],
    "external_scene_source": "",
    "components": [
      {
        "transform2D": {
          "position": {
            "x": 0.0,
            "y": 0.0
          },
          "scale": {
            "x": 1.0,
            "y": 1.0
          },
          "rotation": 0.0,
          "z_index": 0,
          "z_index_relative_to_parent": true,
          "ignore_camera": false
        }
      }
    ],
    "children": []
}
```

---

### Sprite

```json
{
    "name": "Sprite Example",
    "type": "Sprite",
    "tags": [],
    "external_scene_source": "",
    "components": [
      {
        "transform2D": {
          "position": {
            "x": 0.0,
            "y": 0.0
          },
          "scale": {
            "x": 1.0,
            "y": 1.0
          },
          "rotation": 0.0,
          "z_index": 0,
          "z_index_relative_to_parent": true,
          "ignore_camera": false
        }
      },
      {
        "sprite": {
          "texture_path": "assets/images/seika_idle.png",
          "draw_source": {
            "x": 0.0,
            "y": 0.0,
            "width": 48.0,
            "height": 48.0
          },
          "flip_x": false,
          "flip_y": false,
          "modulate": {
            "red": 1.0,
            "blue": 1.0,
            "green": 1.0,
            "alpha": 1.0
          }
        }
      }
    ],
    "children": []
}
```

---

### AnimatedSprite

```json
{
    "name": "AnimatedSprite Example",
    "type": "AnimatedSprite",
    "tags": [],
    "external_scene_source": "",
    "components": [
      {
        "transform2D": {
          "position": {
            "x": 0.0,
            "y": 0.0
          },
          "scale": {
            "x": 1.0,
            "y": 1.0
          },
          "rotation": 0.0,
          "z_index": 0,
          "z_index_relative_to_parent": true,
          "ignore_camera": false
        }
      },
      {
        "animated_sprite": {
          "current_animation": "idle",
          "is_playing": false,
          "flip_x": false,
          "flip_y": false,
          "modulate": {
            "red": 1.0,
            "green": 1.0,
            "blue": 1.0,
            "alpha": 1.0
          },
          "animations": [
            {
              "name": "idle",
              "speed": 100,
              "frames": [
                {
                  "frame": 0,
                  "texture_path": "assets/fighters/puncher/puncher_basic_sheet.png",
                  "draw_source": {
                    "x": 0,
                    "y": 35,
                    "width": 30,
                    "height": 35
                  }
                },
                {
                  "frame": 1,
                  "texture_path": "assets/fighters/puncher/puncher_basic_sheet.png",
                  "draw_source": {
                    "x": 30,
                    "y": 35,
                    "width": 30,
                    "height": 35
                  }
                },
                {
                  "frame": 2,
                  "texture_path": "assets/fighters/puncher/puncher_basic_sheet.png",
                  "draw_source": {
                    "x": 60,
                    "y": 35,
                    "width": 30,
                    "height": 35
                  }
                },
                {
                  "frame": 3,
                  "texture_path": "assets/fighters/puncher/puncher_basic_sheet.png",
                  "draw_source": {
                    "x": 90,
                    "y": 35,
                    "width": 30,
                    "height": 35
                  }
                },
                {
                  "frame": 4,
                  "texture_path": "assets/fighters/puncher/puncher_basic_sheet.png",
                  "draw_source": {
                    "x": 120,
                    "y": 35,
                    "width": 30,
                    "height": 35
                  }
                }
              ]
            },
            {
              "name": "walk",
              "speed": 100,
              "frames": [
                {
                  "frame": 0,
                  "texture_path": "assets/fighters/puncher/puncher_basic_sheet.png",
                  "draw_source": {
                    "x": 0,
                    "y": 0,
                    "width": 30,
                    "height": 35
                  }
                },
                {
                  "frame": 1,
                  "texture_path": "assets/fighters/puncher/puncher_basic_sheet.png",
                  "draw_source": {
                    "x": 30,
                    "y": 0,
                    "width": 30,
                    "height": 35
                  }
                },
                {
                  "frame": 2,
                  "texture_path": "assets/fighters/puncher/puncher_basic_sheet.png",
                  "draw_source": {
                    "x": 60,
                    "y": 0,
                    "width": 30,
                    "height": 35
                  }
                },
                {
                  "frame": 3,
                  "texture_path": "assets/fighters/puncher/puncher_basic_sheet.png",
                  "draw_source": {
                    "x": 90,
                    "y": 0,
                    "width": 30,
                    "height": 35
                  }
                },
                {
                  "frame": 4,
                  "texture_path": "assets/fighters/puncher/puncher_basic_sheet.png",
                  "draw_source": {
                    "x": 120,
                    "y": 0,
                    "width": 30,
                    "height": 35
                  }
                },
                {
                  "frame": 5,
                  "texture_path": "assets/fighters/puncher/puncher_basic_sheet.png",
                  "draw_source": {
                    "x": 150,
                    "y": 0,
                    "width": 30,
                    "height": 35
                  }
                },
                {
                  "frame": 6,
                  "texture_path": "assets/fighters/puncher/puncher_basic_sheet.png",
                  "draw_source": {
                    "x": 180,
                    "y": 0,
                    "width": 30,
                    "height": 35
                  }
                },
                {
                  "frame": 7,
                  "texture_path": "assets/fighters/puncher/puncher_basic_sheet.png",
                  "draw_source": {
                    "x": 210,
                    "y": 0,
                    "width": 30,
                    "height": 35
                  }
                },
                {
                  "frame": 8,
                  "texture_path": "assets/fighters/puncher/puncher_basic_sheet.png",
                  "draw_source": {
                    "x": 240,
                    "y": 0,
                    "width": 30,
                    "height": 35
                  }
                },
                {
                  "frame": 9,
                  "texture_path": "assets/fighters/puncher/puncher_basic_sheet.png",
                  "draw_source": {
                    "x": 270,
                    "y": 0,
                    "width": 30,
                    "height": 35
                  }
                }
              ]
            }
          ]
        }
      }
    ],
    "children": []
}
```

---

### TextLabel

```json
{
    "name": "TextLabel Example",
    "type": "TextLabel",
    "tags": [],
    "external_scene_source": "",
    "components": [
      {
        "transform2D": {
          "position": {
            "x": 0.0,
            "y": 0.0
          },
          "scale": {
            "x": 1.0,
            "y": 1.0
          },
          "rotation": 0.0,
          "z_index": 0,
          "z_index_relative_to_parent": true,
          "ignore_camera": false
        }
      },
      {
        "text_label": {
          "text": "Test text...",
          "font_uid": "verdana",
          "color": {
            "red": 0.0,
            "green": 1.0,
            "blue": 1.0,
            "alpha": 1.0
          },
          "word_wrap": true,
          "max_characters_per_line": 20,
          "new_line_padding": 4
        }
      }
    ],
    "children": []
}
```

---

### CollisionShape2D

```json
{
    "name": "CollisionShape2D Example",
    "type": "CollisionShape2D",
    "tags": [],
    "external_scene_source": "",
    "components": [
      {
        "transform2D": {
          "position": {
            "x": 0.0,
            "y": 0.0
          },
          "scale": {
            "x": 1.0,
            "y": 1.0
          },
          "rotation": 0.0,
          "z_index": 0,
          "z_index_relative_to_parent": true,
          "ignore_camera": false
        }
      },
      {
        "collider": {
          "rectangle": {
            "x": 0.0,
            "y": 0.0,
            "width": 16.0,
            "height": 16.0
          },
          "color": {
            "red": 0.37,
            "green": 0.80,
            "blue": 0.89,
            "alpha": 0.75
          }
        }
      }
    ],
    "children": []
}
```

---

### Spatial

```json
{
    "name": "Spatial Example",
    "type": "Spatial",
    "tags": [],
    "external_scene_source": "",
    "components": [
      {
        "transform3D": {
          "position": {
            "x": 0.0,
            "y": 0.0,
            "z": 0.0
          },
          "scale": {
            "x": 1.0,
            "y": 1.0,
            "z": 1.0
          },
          "rotation": 0.0,
          "rotation_axis": {
            "x": 0.0,
            "y": 0.0,
            "z": 0.0
          }
        }
      }
    ],
    "children": []
}
```

---

### TextureCube

```json
{
    "name": "TextureCube Example",
    "type": "TextureCube",
    "tags": [],
    "external_scene_source": "",
    "components": [
      {
        "transform3D": {
          "position": {
            "x": 0.0,
            "y": 0.0,
            "z": 0.0
          },
          "scale": {
            "x": 1.0,
            "y": 1.0,
            "z": 1.0
          },
          "rotation": 0.0,
          "rotation_axis": {
            "x": 0.0,
            "y": 0.0,
            "z": 0.0
          }
        }
      },
      {
        "texture_cube": {}
      },
      {
        "material": {
          "ambient": {
            "x": 1.0,
            "y": 0.5,
            "z": 0.31
          },
          "diffuse": {
            "x": 1.0,
            "y": 0.5,
            "z": 0.31
          },
          "specular": {
            "x": 0.5,
            "y": 0.5,
            "z": 0.5
          },
          "shininess": 32.0,
          "diffuse_map_texture_path": "assets/container.png",
          "specular_map_texture_path": "assets/container_specular.png"
        }
      }
    ],
    "children": []
}
```

---

### DirectionalLight

```json
{
    "name": "DirectionalLight Example",
    "type": "DirectionalLight",
    "tags": [],
    "external_scene_source": "",
    "components": [
      {
        "transform3D": {
          "position": {
            "x": 0.0,
            "y": 0.0,
            "z": 0.0
          },
          "scale": {
            "x": 1.0,
            "y": 1.0,
            "z": 1.0
          },
          "rotation": 0.0,
          "rotation_axis": {
            "x": 0.0,
            "y": 0.0,
            "z": 0.0
          }
        }
      },
      {
        "directional_light": {
          "direction": {
            "x": -0.2,
            "y": -1.0,
            "z": -0.3
          }
        }
      },
      {
        "material": {
          "ambient": {
            "x": 0.05,
            "y": 0.05,
            "z": 0.05
          },
          "diffuse": {
            "x": 0.4,
            "y": 0.4,
            "z": 0.4
          },
          "specular": {
            "x": 0.5,
            "y": 0.5,
            "z": 0.5
          },
          "shininess": 0.0,
          "diffuse_map_texture_path": "",
          "specular_map_texture_path": ""
        }
      }
    ],
    "children": []
}
```

---

### PointLight

```json
{
    "name": "PointLight Example",
    "type": "PointLight",
    "tags": [],
    "external_scene_source": "",
    "components": [
      {
        "transform3D": {
          "position": {
            "x": 0.0,
            "y": 0.0,
            "z": 0.0
          },
          "scale": {
            "x": 1.0,
            "y": 1.0,
            "z": 1.0
          },
          "rotation": 0.0,
          "rotation_axis": {
            "x": 0.0,
            "y": 0.0,
            "z": 0.0
          }
        }
      },
      {
        "point_light": {
          "linear": 0.09,
          "quadratic": 0.032,
          "constant": 1.0
        }
      },
      {
        "material": {
          "ambient": {
            "x": 0.05,
            "y": 0.05,
            "z": 0.05
          },
          "diffuse": {
            "x": 0.8,
            "y": 0.8,
            "z": 0.8
          },
          "specular": {
            "x": 1.0,
            "y": 1.0,
            "z": 1.0
          },
          "shininess": 0.0,
          "diffuse_map_texture_path": "",
          "specular_map_texture_path": ""
        }
      }
    ],
    "children": []
}
```

---

### SpotLight

```json
{
    "name": "SpotLight Example",
    "type": "SpotLight",
    "tags": [],
    "external_scene_source": "",
    "components": [
      {
        "transform3D": {
          "position": {
            "x": 0.0,
            "y": 0.0,
            "z": 0.0
          },
          "scale": {
            "x": 1.0,
            "y": 1.0,
            "z": 1.0
          },
          "rotation": 0.0,
          "rotation_axis": {
            "x": 0.0,
            "y": 0.0,
            "z": 0.0
          }
        }
      },
      {
        "spot_light": {
          "direction": {
            "x": 0.0,
            "y": 0.0,
            "z": 0.0
          },
          "is_attached_to_camera": true,
          "linear": 0.09,
          "quadratic": 0.032,
          "constant": 1.0,
          "cutoff": 12.5,
          "outer_cutoff": 15.0
        }
      },
      {
        "material": {
          "ambient": {
            "x": 0.0,
            "y": 0.0,
            "z": 0.0
          },
          "diffuse": {
            "x": 1.0,
            "y": 1.0,
            "z": 1.0
          },
          "specular": {
            "x": 1.0,
            "y": 1.0,
            "z": 1.0
          },
          "shininess": 0.0,
          "diffuse_map_texture_path": "",
          "specular_map_texture_path": ""
        }
      }
    ],
    "children": []
}
```

---

## Misc

### Scriptable

A scriptable component can be attached to any NodeType.

```json
{
    "name": "Scriptable Example",
    "type": "Node",
    "tags": [],
    "external_scene_source": "",
    "components": [
      {
        "scriptable_class": {
          "class_path": "src.main",
          "class_name": "Main"
        }
      }
    ],
    "children": []
}
```

---

### Children

All nodes can have nested children.

```json
{
    "name": "Parent Example",
    "type": "Node",
    "tags": [],
    "external_scene_source": "",
    "components": [],
    "children": [
      {
        "name": "Child Example",
        "type": "Node",
        "tags": [],
        "external_scene_source": "",
        "components": [],
        "children": []
      }
    ]
}
```

---
