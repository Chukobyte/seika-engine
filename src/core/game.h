#ifndef GAME_H
#define GAME_H

#include "utils/logger.h"
#include "engine_context.h"
#include "rendering/render_context.h"
#include "project_properties.h"

class Game {
  private:
    Logger *logger = nullptr;
    EngineContext *engineContext = nullptr;
    RenderContext *renderContext = nullptr;
    ProjectProperties projectProperties;

    void InitializeSDL();

    void InitializeRendering();
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
