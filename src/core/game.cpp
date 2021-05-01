#include "game.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include "global_dependencies.h"

Game::Game() {
    logger = Logger::GetInstance();
    logger->SetLogLevel(LogLevel_DEBUG);
    engineContext = GD::GetContainer()->engineContext;
    renderContext = GD::GetContainer()->renderContext;
}

void Game::Initialize() {
    logger->Debug("Roll Back Engine " + engineContext->GetEngineVersion() + " Started!");
    InitializeSDL();
    InitializeRendering();
    engineContext->SetRunning(true);
}

void Game::InitializeSDL() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        logger->Error("Error on initializing SDL\n" + std::string(SDL_GetError()));
        return;
    }

    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        logger->Error("SDL_mixer could not initialized!");
        return;
    }
}

void Game::InitializeRendering() {
    // OpenGL attributes
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    renderContext->window = SDL_CreateWindow(
                                projectProperties.gameTitle.c_str(),
                                SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED,
                                projectProperties.windowWidth,
                                projectProperties.windowHeight,
                                renderContext->windowFlags);
    renderContext->gl_context = SDL_GL_CreateContext(renderContext->window);

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        logger->Error("Couldn't initialize glad");
    }

    renderContext->InitializeFont();
}

void Game::ProcessInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch(event.type) {
        case SDL_QUIT:
            engineContext->SetRunning(false);
            break;
        case SDL_WINDOWEVENT:
            switch (event.window.event) {
            case SDL_WINDOWEVENT_RESIZED:
                const float windowWidth = event.window.data1;
                const float windowHeight = event.window.data2;
                glViewport(0, 0, windowWidth, windowHeight);
                break;
            }
            break;
        }
    }
}

void Game::Update() {}

void Game::Render() {
    glClearColor(projectProperties.backgroundDrawColor.r,
                 projectProperties.backgroundDrawColor.g,
                 projectProperties.backgroundDrawColor.b,
                 projectProperties.backgroundDrawColor.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    SDL_GL_SwapWindow(renderContext->window);
}

bool Game::IsRunning() {
    return engineContext->IsRunning();
}

void Game::Destroy() {
    SDL_GL_DeleteContext(renderContext->gl_context);
    SDL_DestroyWindow(renderContext->window);
    SDL_Quit();
    logger->Debug("Engine exited!");
}