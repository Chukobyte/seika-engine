#ifndef GAME_H
#define GAME_H

#include "utils/logger.h"
#include "engine_context.h"

class Game {
  private:
    Logger *logger = nullptr;
    EngineContext *engineContext = nullptr;
  public:
    Game();

    void Initialize();

    void ProcessInput();

    void Update();

    void Render();

    bool IsRunning();

    void Destroy();
};


#endif //GAME_H
