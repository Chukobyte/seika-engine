# seika.camera

## Camera2D

Engine representation of a 2D camera.


### Properties

None.

---

### Signals

None.

---

### Methods

```python
set_zoom(zoom: seika.math.Vector2) -> None:
```

Sets the camera's zoom.

```python
get_zoom() -> seika.math.Vector2:
```

Gets the camera's zoom.

```python
set_viewport_position(zoom: seika.math.Vector2) -> None:
```

Sets the camera's viewport position.

```python
get_viewport_position() -> seika.math.Vector2:
```

Gets the camera's viewport position.

```python
set_offset(zoom: seika.math.Vector2) -> None:
```

Sets the camera's offset.

```python
get_offset() -> seika.math.Vector2:
```

Gets the camera's offset.

---

## Camera3D

Engine representation of a 3D camera.


### Properties

None.

---

### Signals

None.

---

### Methods

```python
move_left(speed: float) -> None:
```

Move the camera left by a certain speed.

```python
move_right(speed: float) -> None:
```

Move the camera right by a certain speed.

```python
move_up(speed: float) -> None:
```

Move the camera up by a certain speed.

```python
move_down(speed: float) -> None:
```

Move the camera down by a certain speed.

```python
add_yaw(speed: float) -> None:
```

Adds yaw to the camera to rotate based on the passed in speed.

```python
add_pitch(speed: float) -> None:
```

Adds pitch to the camera to rotate based on the passed in speed.

---