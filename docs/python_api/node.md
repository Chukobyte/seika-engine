# roll.node

## Node

**Inherits**: N/A.

Class used as an interface for scene node functionality.  Base class for all scene node types.

### Variables

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
new() -> seika.nodes.Node:
```

Used to create a new node and maps an engine entity to the script's node instance.  If the intent is for a node to eventually be deleted, it should be done either with `queue_free()`, once the node's parent is deleted, or once the scene that the node is currently in is changed/deleted.

```python
queue_deletion() -> None:
```

Queues a node to be deleted and removed from a scene if it's currently added to the scene tree.

```python
add_child(node: Node) -> None:
```

Adds a node as a child to the current node.

```python
create_signal(signal_id: str) -> None:
```

Creates a signal for subscribers to listen to.

```python
connect_signal(signal_id: str, listener_node: seika.nodes.Node, function_name: str) -> None:
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

### Variables

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

### Variables

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

### Variables

```python
animation: seika.assets.Animation
```

Current node's animation.

```python
current_index: int
```

Current node's animation index.

```python
is_playing: bool
```

Returns `True` if an animation is currently playing.

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
stop() -> None:
```

Stops currently playing animation.

---

## TextLabel

**Inherits**: [Node2D](#node2d) -> [Node](#node)

### Variables

```python
text: str
```

Node's label text.

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
