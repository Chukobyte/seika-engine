#ifndef GAME_H
#define GAME_H

#include "utils/logger.h"
#include "engine_context.h"
#include "rendering/render_context.h"
#include "rendering/renderer.h"
#include "project_properties.h"
#include "input/input_manager.h"

class Game {
  private:
    Logger *logger = nullptr;
    EngineContext *engineContext = nullptr;
    RenderContext *renderContext = nullptr;
    Renderer *renderer = nullptr;
    ProjectProperties *projectProperties = nullptr;
    InputManager *inputManager = nullptr;

    void InitializeSDL();

    void InitializeRendering();

    void InitializeECS();
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
