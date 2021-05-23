# roll.math

## Math

Generic math functions

### Properties

None.

---

### Signals

None.

---

### Methods

```python
lerp(source: float, destination: float, amount: float) -> float:
```

Linearly interpolate between two values.

---

## Vector2

Engine representation of a two-dimensional vector.

### Properties

```python
x : float
```
X coordinate.

```python
y : float
```
Y coordinate.

---

### Signals

None.

---

### Methods

```python
dot_product(value: roll.math.Vector2) -> float:
```

Returns the dot product of two Vector2 items.

```python
lerp(source: roll.math.Vector2, destination: roll.math.Vector2, amount: float) -> roll.math.Vector2:
```

Returns the linearly interpolated value of two points.

---

**Static functions that return specific values**

```python
ZERO() -> Vector2(0.0, 0.0):
LEFT() -> Vector2(-1.0, 0.0):
RIGHT() -> Vector2(0.0, 1.0):
UP() -> Vector2(0.0, -1.0):
DOWN() -> Vector2(0.0, 1.0):
```

---

## Vector3

Engine representation of a two dimensional vector.

### Properties

```python
x : float
```

X coordinate.

```python
y : float
```

Y coordinate.

```python
z : float
```

Z coordinate.

---

### Signals

None.

---

### Methods

None.

---

## Rect2

Engine representation of a rectangle vector.

### Properties

```python
x : float
```

X coordinate.

```python
y : float
```

Y coordinate.

```python
w : float
```

Rectangle's width.

```python
h : float
```

Rectangle's height.

---

### Signals

None.

---

### Methods

None.

---
