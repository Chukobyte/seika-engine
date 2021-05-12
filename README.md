# Roll Back Engine

A 2D game engine that's used for a work in progress fighting game.  Windows only for now, but may support other platforms in the future.  Full documentation can be found [here](https://chukobyte.github.io/roll-back-engine/).

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

##### Architecture

Systems and their connections.

```mermaid

graph LR;
    C[Audio]
    D[Rendering]
    E[Physics]
    E-->D
    F[Input]
    F-->G
    F-->E
    G[Scripting]
    G-->C
    G-->I
    G-->J
    G-->K
    H[Assets]
    H-->C
    H-->D
    H-->G
    H-->K
    I[Timer]
    J[Networking]
    J-->D
    K[Animations]
    K-->D
```
