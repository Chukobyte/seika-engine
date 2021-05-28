# Seika Engine

An open source 2D/3D game engine.  Windows only for now, but may support other platforms in the future.  Full documentation can be found [here](https://chukobyte.github.io/seika-engine/).

### Dependencies & Tools

* [SDL2](https://www.libsdl.org/download-2.0.php)
* [SDL2 mixer](https://libsdl.org/projects/SDL_mixer/)
* [Freetype Library](https://www.freetype.org/download.html)
* [GNU Make](http://gnuwin32.sourceforge.net/packages/make.htm)
* [7Zip](https://www.7-zip.org/download.html)

### Instructions

1. Must install Make in order to run commands.

2. Dependent DLLs must be available before running the game.  Download [here](https://www.dropbox.com/s/0439l1btc76wbef/rbe_windows_dependencies.zip?dl=1) and extract in the project's root directory.

##### Build and Compile Game

`make build`

##### Run Game

`make run`

##### Clean Project

`make clean`

##### Format

`make format`

*Must have astyle installed and added to `PATH`.

##### Package and Export Game

`make package`

*Must have 7zip installed and added to the `PATH`.

### Developing with Python API

To help with developing within IDEs, a helper module can be installed to provide a 'Mock' version of the python API.

`pip install -i https://test.pypi.org/simple/ seika-engine-api`

*Note: Kept up to date with the latest release version of the engine.  Support for previous versions may be limited.*

### How To Contribute

There are 3 main ways to contribute to the engine.

1. Code changes to the engine
2. A project within the `assets/game_projects` directory.
3. Documentation additions and changes within the `docs` folder.

It's simple to contribute to seika engine, follow the easy steps below:

1. Create a fork of the seika-engine repo.
2. Make sure to pull the latest from main before pushing up changes.
3. Submit a pull request to the main branch stating the reason for the change.
4. Once a pull request is submitted, changes may be requested and/or additional information may be requested.
