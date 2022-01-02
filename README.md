# Seika Engine


![Seika Engine Editor Screenshot](https://raw.githubusercontent.com/Chukobyte/seika-engine/main/assets/images/docs/seika_engine_editor_preview.gif)

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

3. Set environment variables:

   | Name             | Description                                |
   |:----------------:|:------------------------------------------:|
   | PYTHON_INCLUDE   | Include folder of the python installation. |
   | PYTHON_LIBS      | Python lib folder containing .a files.     |
   | SDL2_INCLUDE     | Include folder for SDL2.                   |
   | SDL2_LIBS        | SDL2 lib folder containing .a files.       |
   | FREETYPE_INCLUDE | Freetype include folder.                   |
   | FREETYPE_LIBS    | Freetype lib folder containing .a files.   |

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

### Prepackaged Builds with Editor

I have recently released packages that contains both the engine and editor and can be found [here on itch.io](https://chukobyte.itch.io/seika).  The combined engine and editor will use a different version scheme and will effectively use v0.x for alpha (current state) and v1.x once it becomes stable.  This is the recommended path to build games with the engine as setting up a scene is more streamlined in the editor.

### Project Showcase

Games and projects made with Seika can be found [here](https://chukobyte.github.io/seika-engine/showcase/projects_made_with_seika/).
