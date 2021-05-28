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
play_music(music_id: str) -> None:
```

Plays music.


```python
stop_music() -> None:
```

Stops currently playing music.

```python
set_music_volume(volume: int) -> None:
```

Sets volume for music.

```python
play_sound(sound_id: str) -> None:
```

Plays a sound.

```python
set_sounds_volume(volume: int) -> None:
```

Sets volume for sounds.

```python
set_all_volume(volume: int) -> None:
```

Sets volume for all audio.

---