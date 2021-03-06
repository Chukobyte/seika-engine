# seika.node

## Node

**Inherits**: N/A.

Class used as an interface for scene node functionality.  Base class for all scene node types.

### Properties

```python
name : str
```

Unique name of node once added to the scene.

```python
entity_id : int
```

Unique id of entity.

```python
tags : List[str]
```

List of tags that has been assigned to an entity.

```pythons
visibility : bool
```

Visibility of a node.  Also affects a node's children visibility.

---

### Signals

None.

---

### Methods

```python
@classmethod
new() -> seika.node.Node:
```

Will create a new instance of either `Node` or any class that inherits it.  Must be added to the scene tree from a node that exists within the scene with the `add_child` method.

```python
queue_deletion() -> None:
```

Queues a node to be deleted and removed from a scene if it's currently added to the scene tree.

```python
add_child(node: Node) -> None:
```

Adds a node as a child to the current node.

```python
get_node(name: str) -> seika.node.Node:
```

Returns a node with the given name.  Will be `None` if node is not found.

```python
get_parent() -> seika.node.Node:
```

Returns the node's parent node.  Will be `None` if node is root.

```python
get_children() -> list:
```

Returns the node's children nodes.  Won't return child's children.

```python
create_signal(signal_id: str) -> None:
```

Creates a signal for subscribers to listen to.

```python
connect_signal(signal_id: str, listener_node: seika.node.Node, function_name: str) -> None:
```

Connects source node's signal to listener node.

```python
emit_signal(signal_id: str, args=[]) -> None:
```

Emits signal from source node.

```python
show() -> None:
```

Makes a node visible.

```python
hide() -> None:
```

Makes a node invisible.

```python
_start() -> None:
```

Called when entity is loaded into scene tree with all dependencies and children.

```python
_physics_process(delta_time: float) -> None:
```

Called every frame.  `delta_time` is passed in to have a frame consistent with CPU speed.

```python
_end() -> None:
```

Called before entity exits scene tree.

---

## Timer

**Inherits**: [Node](#node)

Class used as an interface for Timer functionality.  Must be added to scene tree in order to be used.

### Properties

```python
wait_time: float
```

A timer's run time.  For example, a `wait_time` of 3.5 is equivalent three and a half seconds.

```python
time_left: float
```

How much time a timer has left to run.  When `time_left` is zero, the timer is stopped.

```python
loops: bool
```

If set to `True` the timer will start again after stopping.

```python
is_stopped: bool
```

If `True` the timer is stopped.

---

### Signals

```python
timeout
```

Emitted when a timer's `time_left` reached zero.

---

### Methods

```python
start(wait_time: Optional[float] = None) -> None:
```

Will start a timer.  Will update the `wait_time` property of a timer if the `wait_time` parameter is not `None`.

```python
stop() -> None:
```

Will stop a timer.  `timeout` signal will not be triggered.

```python
pause() -> None:
```

Pauses a timer.  Doesn't have an effect if paused already.

```python
resume() -> None:
```

Resumes a paused timer.

---

## Node2D

**Inherits**: [Node](#node)

Class used as an interface for scene 2D functionality.  Base class for all 2D scene node types.

### Properties

```python
position: seika.math.Vector2
```

Current position of entity.

```python
rotation: float
```

Current rotation in degrees of entity.

---

### Signals

None.

---

### Methods

```python
get_position() -> seika.math.Vector2:
```

Get node's current position.

```python
set_position(value: seika.math.Vector2) -> None:
```

Set node's current position.

```python
add_to_position(value: seika.math.Vector2) -> None:
```

Add to node's current position.  For example, if this line of code is within the `_process` function, the output of this line of code `node.add_to_position(Vector(5, 10))` within 3 frames will be `[(5, 10), (10, 20), (15, 30)]`.

---

## Sprite

**Inherits**: [Node2D](#node2d) -> [Node](#node)

Class used to render a sprite entity.

### Properties

```python
flip_h: bool
```

Determines whether the x axis is flipped.

```python
flip_v: bool
```

Determines whether the y axis is flipped.

```python
modulate: seika.color.Color
```

Node's color modulation.

```python
texture: seika.assets.Texture
```

Node's [texture](assets.md#texture).

```python
draw_source: seika.math.Rect2
```

Node's draw source represented as a [Rect2](math.md#rect2).  Will draw the loaded texture that's within the bounds of the [Rect2](math.md#rect2).

---

### Signals

None.

---


### Methods

None.

---

## AnimatedSprite

**Inherits**: [Node2D](#node2d) -> [Node](#node)

Class used to render an animated sprite entity.

### Properties

```python
is_playing: bool
```

Returns `True` if an animation is currently playing.

```python
modulate: seika.color.Color
```

Node's color modulation.

```python
frame: int
```

Current frame of animation.

```python
animation_frames: int
```

Amount of frames for current animation.

```python
animation_speed: int
```

Speed of current animation in milliseconds per frame.

```python
flip_h: bool
```

Detemines whether the x axis is flipped.

```python
flip_v: bool
```

Detemines whether the y axis is flipped.

---

### Signals

```python
animation_finished
```

Emitted when an animations is finished.

```python
frame_changed
```

Emitted when an animation frame changes.

---

### Methods

```python
play(animation_name: str, start_frame = 0) -> None:
```

Plays animation based on the name passed in.

```python
set_animation(animation_name: str) -> None:
```

Sets the current animation based on the name passed in.

```python
stop() -> None:
```

Stops the currently playing animation.

---

## TextLabel

**Inherits**: [Node2D](#node2d) -> [Node](#node)

Class used to render font.

### Properties

```python
text: str
```

Text Label's text.

```python
color: seika.color.Color
```

Color of the text.

```python
font: seika.assets.Font
```

The [font](assets.md#font) of the text.

```python
word_wrap: bool
```

Determines if the textlabel has word wrapping enabled.

```python
max_characters_per_line: int
```

How many characters per line a text label can display.  Must have `word_wrap` set to `True` to take effect.

```python
new_line_padding: int
```

Vertical padding for new lines.  Must have `word_wrap` set to `True` to take effect.

---

### Signals

None.

---

### Methods

```python
get_text() -> str:
```

Get node's label text.

```python
set_text(value: str) -> None:
```

Set node's label text.

---

## CollisionShape2D

**Inherits**: [Node2D](#node2d) -> [Node](#node)

Class used to define collision shapes defined as rectangles.  May add other collision shapes in the future.

### Properties

```python
collider_rect: seika.math.Rect2
```

Collision shape's colliding rectangle.

```python
color: seika.color.Color
```

A collider's color.  Only shown when `colliders_visible` is enabled in [project properties](../general/project_properties.md).

```python
is_under_mouse: bool
```

Returns `True` if mouse cursor is on top of `collider_rect`.

---

### Signals

None.

---

### Methods

```python
add_collision_exception(node: seika.node.Node) -> None:
```

Adds a node to an exception list to ignore collisions.

```python
remove_collision_exception(node: seika.node.Node) -> None:
```

Removes a node from an exception list. Collisions between nodes are enabled.

---

## Spatial

**Inherits**: [Node](#node)

Base class for 3D entities.

### Properties

```python
position: seika.math.Vector3
```

Spatial's position represented as a `Vector3`.

---

### Signals

None.

---

### Methods

```python
add_to_position(value: seika.math.Vector3) -> None:
```

Adds passed in value to the Spatial's position.

---

## TextureCube

**Inherits**: [Spatial](#spatial) -> [Node](#node)

Class that represents 3D cubes with textures.

### Properties

None.

---

### Signals

None.

---

### Methods

None.

---

## DirectionalLight

**Inherits**: [Spatial](#spatial) -> [Node](#node)

Class representing a directional light.

### Properties

```python
direction: seika.math.Vector3
```

The direction that the light is pointing.

---

### Signals

None.

---

### Methods

None.

---

## PointLight

**Inherits**: [Spatial](#spatial) -> [Node](#node)

Class representing a directional light.

### Properties

```python
cutoff: float
```

The cutoff for the light's inner cone.

```python
outer_cutoff: float
```

The cutoff for the light's outer cone.

---

### Signals

None.

---

### Methods

None.

---

## SpotLight

**Inherits**: [Spatial](#spatial) -> [Node](#node)

Class representing a spotlight.

### Properties

```python
direction: seika.math.Vector3
```

The direction that the light is pointing.

---

### Signals

None.

---

### Methods

None.

---
