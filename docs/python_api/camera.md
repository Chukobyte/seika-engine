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
@staticmethod
set_zoom(zoom: seika.math.Vector2) -> None:
```

Sets the camera's zoom.

```python
@staticmethod
get_zoom() -> seika.math.Vector2:
```

Gets the camera's zoom.

```python
@staticmethod
set_viewport_position(zoom: seika.math.Vector2) -> None:
```

Sets the camera's viewport position.

```python
@staticmethod
get_viewport_position() -> seika.math.Vector2:
```

Gets the camera's viewport position.

```python
@staticmethod
set_offset(zoom: seika.math.Vector2) -> None:
```

Sets the camera's offset.

```python
@staticmethod
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
@staticmethod
move_left(speed: float) -> None:
```

Move the camera left by a certain speed.

```python
@staticmethod
move_right(speed: float) -> None:
```

Move the camera right by a certain speed.

```python
@staticmethod
move_up(speed: float) -> None:
```

Move the camera up by a certain speed.

```python
@staticmethod
move_down(speed: float) -> None:
```

Move the camera down by a certain speed.

```python
@staticmethod
add_yaw(speed: float) -> None:
```

Adds yaw to the camera to rotate based on the passed in speed.

```python
@staticmethod
add_pitch(speed: float) -> None:
```

Adds pitch to the camera to rotate based on the passed in speed.

---
