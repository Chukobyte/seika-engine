# seika.audio

## Audio

Interface for music and sound effects.  Music will continue to loop until stopped and sound is only played once.

### Properties

None.

---

### Signals

None.

---

### Methods

```python
@staticmethod
play_music(music_id: str, loops=True) -> None:
```

Plays music, will loop is `loops` is set to `True`.


```python
@staticmethod
stop_music() -> None:
```

Stops currently playing music.

```python
@staticmethod
set_music_volume(volume: int) -> None:
```

Sets volume for music.

```python
@staticmethod
play_sound(sound_id: str) -> None:
```

Plays a sound.

```python
@staticmethod
set_sounds_volume(volume: int) -> None:
```

Sets volume for sounds.

```python
@staticmethod
set_all_volume(volume: int) -> None:
```

Sets volume for all audio.

---