# seika.physics

## Collision

Interface for collisions between entities.  This interface most likely will be updated in the near future.

### Properties

None.

---

### Signals

None.

---

### Methods

```python
get_collided_nodes(node: seika.node.Node) -> bool:
```

Returns a `list` of nodes that collided with the passed in `node`.

```python
update_collisions(node: seika.node.Node) -> None:
```

Updates collision data for a `node`.

---