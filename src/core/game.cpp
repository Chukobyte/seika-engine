#include "game.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include "global_dependencies.h"

#include "ecs/entity/system/sprite_rendering_entity_system.h"
#include "ecs/entity/system/text_rendering_entity_system.h"

#include "ecs/component/components/text_label_component.h"

Game::Game() {
    logger = Logger::GetInstance();
    logger->SetLogLevel(LogLevel_DEBUG);
    projectProperties = ProjectProperties::GetInstance();
    engineContext = GD::GetContainer()->engineContext;
    renderContext = GD::GetContainer()->renderContext;
    renderer = GD::GetContainer()->renderer;
    inputManager = InputManager::GetInstance();
}

void Game::Initialize() {
    logger->Debug("Roll Back Engine " + engineContext->GetEngineVersion() + " Started!");
    InitializeSDL();
    InitializeRendering();
    GD::GetContainer()->assetManager->LoadDefaultAssets(); // TODO: clean up
    InitializeECS();
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

void Game::InitializeECS() {
    EntityComponentOrchestrator *entityComponentOrchestrator = GD::GetContainer()->entityComponentOrchestrator;

    // Components
    entityComponentOrchestrator->RegisterComponent<Transform2DComponent>();
    entityComponentOrchestrator->RegisterComponent<SpriteComponent>();
    entityComponentOrchestrator->RegisterComponent<TextLabelComponent>();

    // Systems
    entityComponentOrchestrator->RegisterSystem<SpriteRenderingEntitySystem>();
    ComponentSignature spriteRenderingSystemSignature;
    spriteRenderingSystemSignature.set(entityComponentOrchestrator->GetComponentType<Transform2DComponent>(), true);
    spriteRenderingSystemSignature.set(entityComponentOrchestrator->GetComponentType<SpriteComponent>(), true);
    entityComponentOrchestrator->SetSystemSignature<SpriteRenderingEntitySystem>(spriteRenderingSystemSignature);

    entityComponentOrchestrator->RegisterSystem<TextRenderingEntitySystem>();
    ComponentSignature textRenderingSystemSignature;
    textRenderingSystemSignature.set(entityComponentOrchestrator->GetComponentType<Transform2DComponent>(), true);
    textRenderingSystemSignature.set(entityComponentOrchestrator->GetComponentType<TextLabelComponent>(), true);
    entityComponentOrchestrator->SetSystemSignature<TextRenderingEntitySystem>(textRenderingSystemSignature);

    // TEMP
    // Creates a Sprite Node
    Entity puncherEntity = entityComponentOrchestrator->CreateEntity();
    Transform2DComponent puncherTransform2DComponent{
        .position = Vector2(projectProperties->windowWidth / 2, projectProperties->windowHeight / 2),
        .scale = Vector2(4.0f, 4.0f)
    };
    entityComponentOrchestrator->AddComponent(puncherEntity, puncherTransform2DComponent);

    Texture2D *puncherTexture = GD::GetContainer()->assetManager->GetTexture("puncher");
    Vector2 puncherSpriteSize = Vector2(12, 16);
    SpriteComponent puncherSpriteComponent{
        .texture = puncherTexture,
        .drawSource = Rect2(0, 0, puncherSpriteSize)
    };
    entityComponentOrchestrator->AddComponent(puncherEntity, puncherSpriteComponent);

    // Creates Text Label Node
    Entity titleEntity = entityComponentOrchestrator->CreateEntity();
    Transform2DComponent titleTransform2DComponent{
        .position = Vector2(325, 100)
    };
    entityComponentOrchestrator->AddComponent(titleEntity, titleTransform2DComponent);

    TextLabelComponent textLabelComponent{
        .text = "Puncher",
        .font = GD::GetContainer()->assetManager->GetFont("bruh"),
        .color = Color(0.0f, 1.0f, 1.0f)
    };
    entityComponentOrchestrator->AddComponent(titleEntity, textLabelComponent);
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
                                projectProperties->gameTitle.c_str(),
                                SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED,
                                projectProperties->windowWidth,
                                projectProperties->windowHeight,
                                renderContext->windowFlags);
    renderContext->gl_context = SDL_GL_CreateContext(renderContext->window);

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        logger->Error("Couldn't initialize glad");
    }

    renderContext->InitializeFont();

    renderer->Initialize();
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
    inputManager->ProcessInputs(event);
}

void Game::Update() {
    // TODO: Clean up temp quit with escape once scripting is implemented
    if (inputManager->IsActionJustPressed(inputManager->QUIT_DEFAULT_ACTION)) {
        engineContext->SetRunning(false);
    }

    inputManager->ClearInputFlags();
}

void Game::Render() {
    glClearColor(projectProperties->backgroundDrawColor.r,
                 projectProperties->backgroundDrawColor.g,
                 projectProperties->backgroundDrawColor.b,
                 projectProperties->backgroundDrawColor.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    static SpriteRenderingEntitySystem *spriteRenderingEntitySystem = (SpriteRenderingEntitySystem*) GD::GetContainer()->entitySystemManager->GetEntitySystem<SpriteRenderingEntitySystem>();
    spriteRenderingEntitySystem->Render();

    static TextRenderingEntitySystem *textRenderingEntitySystem = (TextRenderingEntitySystem*) GD::GetContainer()->entitySystemManager->GetEntitySystem<TextRenderingEntitySystem>();
    textRenderingEntitySystem->Render();

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
