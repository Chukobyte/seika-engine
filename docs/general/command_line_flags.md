# Command Line Flags

## Log Level

`-l` `-log-level`

```
[SEIKA_ENGINE] [LOG_LEVEL_FLAG] [LOG_LEVEL]
```

Sets the log level of the engine to either `DEBUG`, `WARN` ,`INFO`, `ERROR`.

## Project File

`-p` `-project-file`

```
[SEIKA_ENGINE] [PROJECT_FILE_FLAG] [PROJECT_FILE_PATH]
```

Overrides the default path `project.scfg` with the value that's passed in.

## Starting Directory

`-sd` `-starting-directory`

```
[SEIKA_ENGINE] [PROJECT_FILE_FLAG] [ENGINE_EXECUTABLE_DIRECTORY]
```

Overrides the default directory of the engine on startup.  Mostly to be used by the editor.


## Working Directory

`-d` `-working-directory`

```
[SEIKA_ENGINE] [PROJECT_FILE_FLAG] [PROJECT_WORKING_DIRECTORY]
```

Overrides the default working path of the game.  Directory must contain a `project.scfg` file.

## Local Assets

`-la` `-local-assets`

```
[SEIKA_ENGINE] [PROJECT_FILE_FLAG] [FLAG]
```

Determines whether game assets are loaded from flat files or archive.  Defaults to `false`.
