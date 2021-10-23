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
get_collided_nodes(node: seika.node.Node) -> list:
```

Returns a `list` of nodes that collided with the passed in `node`.

```python
@staticmethod
get_nodes_under_mouse() -> list:
```

Returns a `list` of nodes (`CollisionShape2D`) that are under the current mouse's position.

---
