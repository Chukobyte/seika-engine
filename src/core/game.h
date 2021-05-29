#ifndef GAME_H
#define GAME_H

#include "utils/logger.h"
#include "engine_context.h"
#include "rendering/render_context.h"
#include "rendering/renderer.h"
#include "project_properties.h"
#include "input/input_manager.h"
#include "networking/network_context.h"
#include "utils/command_line_flag_helper.h"

class Game {
  private:
    Logger *logger = nullptr;
    EngineContext *engineContext = nullptr;
    RenderContext *renderContext = nullptr;
    Renderer *renderer = nullptr;
    ProjectProperties *projectProperties = nullptr;
    InputManager *inputManager = nullptr;
    NetworkContext *networkContext = nullptr;
    CommandLineFlagHelper commandLineFlagHelper;

    void InitializeSDL();

    void InitializeRendering();

    void InitializeECS();

    void FixedTimeStep();

    void VariableTimeStep(Uint32 lastFrameTime);
  public:
    Game();

    void Initialize(int argv, char** args);

    void ProcessInput();

    void Update();

    void Render();

    bool IsRunning();

    void Destroy();
};


#endif //GAME_H
