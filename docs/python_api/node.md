# roll.node

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

---

### Signals

None.

---

### Methods

```python
queue_deletion() -> None:
```

Queues a node to be deleted and removed from a scene if it's currently added to the scene tree.

```python
add_child(node: Node) -> None:
```

Adds a node as a child to the current node.

```python
get_node(name: str) -> roll.node.Node:
```

Returns a node with the given name.  Will be `None` if node is not found.

```python
create_signal(signal_id: str) -> None:
```

Creates a signal for subscribers to listen to.

```python
connect_signal(signal_id: str, listener_node: roll.node.Node, function_name: str) -> None:
```

Connects source node's signal to listener node.

```python
emit_signal(signal_id: str, args=[]) -> None:
```

Emits signal from source node.

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

## Node2D

**Inherits**: [Node](#node)

Class used as an interface for scene 2D functionality.  Base class for all 2D scene node types.

### Properties

```python
position : roll.math.Vector2
```

Current position of entity.

---

### Signals

None.

---

### Methods

```python
get_position() -> roll.math.Vector2:
```

Get node's current position.

```python
set_position(value: roll.math.Vector2) -> None:
```

Set node's current position.

```python
add_to_position(value: roll.math.Vector2) -> None:
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

Detemines whether the x axis is flipped.

```python
flip_v: bool
```

Detemines whether the y axis is flipped.

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
color: roll.color.Color
```

Color of the text.

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

---

## CollisionShape2D

**Inherits**: [Node2D](#node2d) -> [Node](#node)

Class used to define collision shapes defined as rectangles.  May add other collision shapes in the future.

### Properties

```python
collider_rect: roll.math.Rect2
```

Collision shape's colliding rectangle.

```python
color: roll.color.Color
```

A collider's color.  Only shown when `colliders_visible` is enabled in [project properties](../general/project_properties.md).

---

### Signals

None.

---

### Methods

```python
add_collision_exception(node: roll.node.Node) -> None:
```

Adds a node to an exception list to ignore collisions.

```python
remove_collision_exception(node: roll.node.Node) -> None:
```

Removes a node from an exception list. Collisions between nodes are enabled.

---
