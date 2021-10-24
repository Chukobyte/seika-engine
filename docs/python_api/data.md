# seika.data

## ConfigTool

A tool used to save and load game data.  Game data will be saved/loaded from the user directory.  On Windows the default root path is `C:\Users\$CURRENT_USER\AppData\Roaming\seika_engine\$GAME_TITLE`.

### Properties

```python
file_path : str
```

File path of `ConfigTool`.

```python
data : dict
```

Current data being stored within `ConfigTool`.  Should be serializable to JSON.

---

### Signals

None.

---

### Methods

```python
save_file(encryption_key: Optional[str] = None) -> bool:
```

Save `data` into a file at `file_path`.  If `encryption_key` is passed in, will encrypt the file.  Will return `True` if save is successful.

```python
load_file(encryption_key: Optional[str] = None) -> bool:
```

Loads `data` from a file at `file_path`.  If `encryption_key` is passed in, will decrypt the file before loading.  Will return `True` if loaded successfully.

```python
delete_file() -> bool:
```

Deletes file at `file_path`.  Will return `True` if successfully deleted.

```python
does_file_exist() -> bool:
```

Return `True` if file exists.

### Example Usage

#### Save Game
```python
from seika.node import Node2D
from seika.data import ConfigTool

class Main(Node2D):
    def _start(self) -> None:
        # Save File
        config_tool = ConfigTool(file_path="game.sav", initial_data={"level": 1})
        config_tool.save()

        # Save Encrypted File
        config_tool_secrets = ConfigTool(file_path="game_enc.sav", initial_data={"name": "Amaya"})
        config_tool_secrets.save(encrypted_key="secret_password")
```

#### Load Game
```python
from seika.node import Node2D
from seika.data import ConfigTool

class Main(Node2D):
    def _start(self) -> None:
        # Load File
        config_tool = ConfigTool(file_path="game.sav")
        config_tool.load_file()
        print(f"game.sav = {config_tool.data}") # prints 'game.sav = {"level":1}'

        # Load Encrypted File
        config_tool_secrets = ConfigTool(file_path="game_enc.sav")
        config_tool_secrets.load_file(encrypted_key="secret_password")
        print(f"game_enc.sav = {config_tool_secrets.data}") # prints 'game_enc.sav = {"name":"Amaya"}'
```

---
