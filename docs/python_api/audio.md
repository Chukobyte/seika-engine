# seika.audio

## Audio

Interface for music and sound effects.  Music will continue to loop until stopped and sound is only played once.  Will be deprecated in place of [AudioStream](#audio-stream)

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

## Audio Stream

Interface for audio.  Should be used instead of [Audio](#audio) but care must be taken to zero out the amplitude at the end of samples especially when looping.

### Properties

```python
uid: str
```

Unique identifier for AudioStream.

```python
pitch: float
```

The pitch for the AudioStream, initializes to 1.0 by default.  (Min: 0.0, Max: 1.0)

```python
gain: float
```

The gain (volume) for the AudioStream, initializes to 1.0 by default. (Min: 0.0, Max: 1.0)

```python
loops: bool
```

Determines if the AudioStream will play the sample from the beginning when reaching the end.  Defaults to `False`.

```python
is_playing: bool
```

Returns whether the audio stream is playing or not.

---

### Signals

None.

---

### Methods

```python
@staticmethod
get(uid: str) -> seika.audio.AudioStream:
```

Return a reference to a loaded `AudioStream` object.

```python
play() -> None:
```

Plays the audio loaded into `AudioStream`.

```python
stop() -> None:
```

Stops the audio loaded into `AudioStream`.

---
