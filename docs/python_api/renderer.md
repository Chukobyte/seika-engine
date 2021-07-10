# seika.renderer

## Renderer

Interface for the engine's renderer.

### Properties

None.

---

### Signals

None.

---

### Methods

```python
draw_texture(texture_path: str,
             source_rect: seika.math.Rect2,
             dest_rect: seika.math.Rect2,
             z_index=0,
             rotation=0.0,
             color=seika.color.Color(1.0, 1.0, 1.0, 1.0),
             flip_x=False,
             flip_y=False) -> None:
```

Draws a texture from a relative path.  Texture must have already been loaded by engine to draw.

---
