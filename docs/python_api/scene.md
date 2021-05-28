# seika.scene

## Scene Tree

Represents the scene tree which handles operations related to the scene system.

### Properties

None.

---

### Signals

None.

---

### Methods

```python
change_scene(scene_path: str) -> None:
```

Change the scene to the current scene defined by `scene_path`.

```python
get_current_scene_node() -> seika.node.Node:
```

Returns the root node of the current scene.

---