# seika.physics

## Collision

Interface for collisions between entities.

### Properties

None.

---

### Signals

None.

---

### Methods

```python
@staticmethod
get_collided_nodes(node: seika.node.Node, offset: seika.math.Vector2) -> list:
```

Returns a `list` of nodes that collided with the passed in `node`.  Can configure the position of the collision by adjusting the `offset`.

```python
@staticmethod
get_collided_nodes_by_tag(node: seika.node.Node, tag: str, offset: seika.math.Vector2) -> list:
```

Same as `get_collided_nodes` but filters results by tag.

```python
@staticmethod
get_nodes_under_mouse() -> list:
```

Returns a `list` of nodes (`CollisionShape2D`) that are under the current mouse's position.

---
