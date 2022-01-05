#include "core/game.h"
#include "core/audio/audio_data.h"


int main(int argv, char** args) {
    Game gameEngine(argv, args);

    while (gameEngine.IsRunning()) {
        gameEngine.ProcessInput();
        gameEngine.Update();
        gameEngine.Render();
    }

    return 0;
}
