# seika.assets

## Texture

Engine representation of a texture.  All properties are read only.

### Properties

```python
file_path : str
```

Texture's relative file path.

```python
wrap_s : str
```

String representation of texture's `GL_TEXTURE_WRAP_S`.

```python
wrap_t : str
```

String representation of texture's `GL_TEXTURE_WRAP_T`.

```python
filter_min : str
```

String representation of texture's `GL_TEXTURE_MIN_FILTER`.

```python
filter_max : str
```

String representation of texture's `GL_TEXTURE_MAG_FILTER`.

---

### Signals

None.

---

### Methods

```python
@staticmethod
get(file_path: str) -> seika.assets.Texture:
```

Get texture from relative file path.

---

## Font

Engine representation of a font.  All properties are read only.

### Properties

```python
uid : str
```

Unique id of font.

```python
file_path : str
```

Relative file path of font.

```python
size : int
```

Size of the font.

---

### Signals

None.

---

### Methods

```python
create(uid: str, file_path: str, size: int) -> seika.assets.Font:
```

Creates a new font.

```python
get(uid: str) -> seika.assets.Font:
```

Returns an already existing font.

---
