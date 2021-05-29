#include "core/game.h"


int main(int argv, char** args) {
    static Game *gameEngine = new Game();
    gameEngine->Initialize(argv, args);

    while (gameEngine->IsRunning()) {
        gameEngine->ProcessInput();
        gameEngine->Update();
        gameEngine->Render();
    }

    gameEngine->Destroy();

    return 0;
}
