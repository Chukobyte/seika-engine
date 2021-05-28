# Core Concepts

## Node

Nodes are the basic building block of a game in Seika Engine.  There are many different node types that inherit from the base `Node` class and more information about their API usage can be found [here](../python_api/node.md).  Python scripts can be attached to Nodes to add to their functionality.

## Scene

A scene is a collection of nodes.  Must contain a root node and there can only be one root node per scene.  Scenes can be instanced.  When a scene is destroyed the root node as well as all it's children will also be removed.  In Seika Engine all scenes are stored as json files.  Here is an example of how a scene with just a root node is serialized to json.

```json
{
    "name": "Main",
    "type": "Node",
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
                    "x": 0.0,
                    "y": 0.0
                },
                "rotation": 0,
                "z_index": 0,
                "z_index_relative_to_parent": false,
                "ignore_camera": false
            }
        },
        {
            "scriptable_class": {
                "class_path": "assets.game_projects.fighter.src.init",
                "class_name": "Init"
            }
        }
    ],
    "children": []
}

```

## Scene Tree

The scene tree contains active scenes nodes.  There are two types of active scenes.

**Main Scene** 

The current main scene, there can only be one at a time.
 
**Singleton Scene**

Scenes that are made active when the game is initialized.  They will stay active during the duration of the game unless `queue_deletion()` is called on them.

## Signal

Signals can be used to apply the [observer pattern](https://en.wikipedia.org/wiki/Observer_pattern) to game logic.  They are also used for notifying interested listeners about events for some of the systems within the engine (e.g. joystick disconnecting). Signals are defined within the base [Node](../python_api/node.md#methods) class.

```python
from seika.nodes import AnimatedSprite

class Seika(AnimatedSprite):
	def _start(self) -> None:
		self.connect_signal("animation_finished", self, "_on_AnimatedSprite_animation_finished")
		self.play(animation_name="swim")

	def _on_AnimatedSprite_animation_finished(self, args : list) -> None:
		if self.animation.name == "swim":
			self.play(animation_name="idle")
```

Example to play an animation named 'idle' after the 'swim' animation is played.
