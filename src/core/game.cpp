#include "game.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include "global_dependencies.h"

#include "ecs/entity/system/sprite_rendering_entity_system.h"
#include "ecs/entity/system/animated_sprite_rendering_entity_system.h"
#include "ecs/entity/system/text_rendering_entity_system.h"
#include "ecs/entity/system/script_entity_system.h"

#include "ecs/component/components/animated_sprite_component.h"
#include "ecs/component/components/text_label_component.h"
#include "ecs/component/components/scriptable_class_component.h"

#include "scripting/python/python_script_context.h"

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
    logger->Debug("Roll Back Engine v" + engineContext->GetEngineVersion() + " started!");
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
    entityComponentOrchestrator->RegisterComponent<AnimatedSpriteComponent>();
    entityComponentOrchestrator->RegisterComponent<TextLabelComponent>();
    entityComponentOrchestrator->RegisterComponent<ScriptableClassComponent>();

    // Systems
    entityComponentOrchestrator->RegisterSystem<SpriteRenderingEntitySystem>();
    ComponentSignature spriteRenderingSystemSignature;
    spriteRenderingSystemSignature.set(entityComponentOrchestrator->GetComponentType<Transform2DComponent>(), true);
    spriteRenderingSystemSignature.set(entityComponentOrchestrator->GetComponentType<SpriteComponent>(), true);
    entityComponentOrchestrator->SetSystemSignature<SpriteRenderingEntitySystem>(spriteRenderingSystemSignature);

    entityComponentOrchestrator->RegisterSystem<AnimatedSpriteRenderingEntitySystem>();
    ComponentSignature animatedSpriteRenderingSystemSignature;
    animatedSpriteRenderingSystemSignature.set(entityComponentOrchestrator->GetComponentType<Transform2DComponent>(), true);
    animatedSpriteRenderingSystemSignature.set(entityComponentOrchestrator->GetComponentType<AnimatedSpriteComponent>(), true);
    entityComponentOrchestrator->SetSystemSignature<AnimatedSpriteRenderingEntitySystem>(animatedSpriteRenderingSystemSignature);

    entityComponentOrchestrator->RegisterSystem<TextRenderingEntitySystem>();
    ComponentSignature textRenderingSystemSignature;
    textRenderingSystemSignature.set(entityComponentOrchestrator->GetComponentType<Transform2DComponent>(), true);
    textRenderingSystemSignature.set(entityComponentOrchestrator->GetComponentType<TextLabelComponent>(), true);
    entityComponentOrchestrator->SetSystemSignature<TextRenderingEntitySystem>(textRenderingSystemSignature);

    ScriptEntitySystem* scriptEntitySystem = entityComponentOrchestrator->RegisterSystem<ScriptEntitySystem>();
    scriptEntitySystem->InstallScriptContext<PythonScriptContext>();
    ComponentSignature scriptSystemSignature;
    scriptSystemSignature.set(entityComponentOrchestrator->GetComponentType<ScriptableClassComponent>(), true);
    entityComponentOrchestrator->SetSystemSignature<ScriptEntitySystem>(scriptSystemSignature);

    entityComponentOrchestrator->InitializeAllSystems();

    // TEMP
    // Creates a Sprite Node
//    Entity puncherEntity = entityComponentOrchestrator->CreateEntity();
//    Transform2DComponent puncherTransform2DComponent{
//        .position = Vector2(projectProperties->windowWidth / 2, projectProperties->windowHeight / 2),
//        .scale = Vector2(4.0f, 4.0f)
//    };
//    entityComponentOrchestrator->AddComponent(puncherEntity, puncherTransform2DComponent);
//
//    Texture2D *puncherTexture = GD::GetContainer()->assetManager->GetTexture("puncher");
//    Vector2 puncherSpriteSize = Vector2(12, 16);
//    SpriteComponent puncherSpriteComponent{
//        .texture = puncherTexture,
//        .drawSource = Rect2(0, 0, puncherSpriteSize)
//    };
//    entityComponentOrchestrator->AddComponent(puncherEntity, puncherSpriteComponent);

    // Creates an Animated Sprite Node
    Entity puncherEntity = entityComponentOrchestrator->CreateEntity();
    Transform2DComponent puncherTransform2DComponent{
        .position = Vector2(projectProperties->windowWidth / 2, projectProperties->windowHeight / 2),
        .scale = Vector2(4.0f, 4.0f)
    };
    entityComponentOrchestrator->AddComponent(puncherEntity, puncherTransform2DComponent);

    Texture2D *puncherTexture = GD::GetContainer()->assetManager->GetTexture("puncher");
    Vector2 puncherSpriteSize = Vector2(12, 16);
    std::map<unsigned int, AnimationFrame> puncherIdleAnimationFrames;
    AnimationFrame puncherIdleFrame0{
        .texture = puncherTexture,
        .drawSource = Rect2(0, 0, puncherSpriteSize),
        .frame = 0
    };
    puncherIdleAnimationFrames.emplace(puncherIdleFrame0.frame, puncherIdleFrame0);
    AnimationFrame puncherIdleFrame1{
        .texture = puncherTexture,
        .drawSource = Rect2(12, 0, puncherSpriteSize),
        .frame = 1
    };
    puncherIdleAnimationFrames.emplace(puncherIdleFrame1.frame, puncherIdleFrame1);
    AnimationFrame puncherIdleFrame2{
        .texture = puncherTexture,
        .drawSource = Rect2(24, 0, puncherSpriteSize),
        .frame = 2
    };
    puncherIdleAnimationFrames.emplace(puncherIdleFrame2.frame, puncherIdleFrame2);
    AnimationFrame puncherIdleFrame3{
        .texture = puncherTexture,
        .drawSource = Rect2(36, 0, puncherSpriteSize),
        .frame = 3
    };
    puncherIdleAnimationFrames.emplace(puncherIdleFrame3.frame, puncherIdleFrame3);
    AnimationFrame puncherIdleFrame4{
        .texture = puncherTexture,
        .drawSource = Rect2(48, 0, puncherSpriteSize),
        .frame = 4
    };
    puncherIdleAnimationFrames.emplace(puncherIdleFrame4.frame, puncherIdleFrame4);
    AnimationFrame puncherIdleFrame5{
        .texture = puncherTexture,
        .drawSource = Rect2(60, 0, puncherSpriteSize),
        .frame = 5
    };
    puncherIdleAnimationFrames.emplace(puncherIdleFrame5.frame, puncherIdleFrame5);

    Animation puncherAnimation{
        .name = "Idle",
        .speed = 100,
        .animationFrames = puncherIdleAnimationFrames,
        .frames = puncherIdleAnimationFrames.size()
    };
    std::map<std::string, Animation> puncherIdleAnimations;
    puncherIdleAnimations.emplace(puncherAnimation.name, puncherAnimation);
    AnimatedSpriteComponent puncherAnimatedSpriteComponent{
        .animations = puncherIdleAnimations,
        .currentAnimation = puncherIdleAnimations["Idle"],
        .currentFrameIndex = 0,
        .isPlaying = true
    };
    entityComponentOrchestrator->AddComponent(puncherEntity, puncherAnimatedSpriteComponent);

    ScriptableClassComponent puncherScriptableClassComponent{
        .classPath = "assets.game_projects.test.src.fighter",
        .className = "Puncher"
    };
    entityComponentOrchestrator->AddComponent(puncherEntity, puncherScriptableClassComponent);
    scriptEntitySystem->CreateEntityInstance(puncherEntity);

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
    // Sleep until FRAME_TARGET_TIME has elapsed since last frame
    static Uint32 lastFrameTime = 0;
    const unsigned int FRAME_TARGET_TIME = projectProperties->GetMillisecondsPerTick() / projectProperties->GetTargetFPS();
    unsigned int timeToWait = FRAME_TARGET_TIME - (SDL_GetTicks() - lastFrameTime);
    if (timeToWait > 0 && timeToWait <= FRAME_TARGET_TIME) {
        SDL_Delay(timeToWait);
    }

    FixedTimeStep();

    VariableTimeStep(lastFrameTime);

    lastFrameTime = SDL_GetTicks();
}

void Game::FixedTimeStep() {
    // Fixed time step
    static double time = 0.0f;
    const double PHYSICS_DELTA_TIME = projectProperties->GetFixedPhysicsDeltaTime();
    static Uint32 currentTime = SDL_GetTicks();
    static double accumulator = 0.0f;

    Uint32 newTime = SDL_GetTicks();
    Uint32 frameTime = newTime - currentTime;
    const Uint32 MAX_FRAME_TIME = 250;
    if (frameTime > MAX_FRAME_TIME) {
        frameTime = MAX_FRAME_TIME;
    }
    currentTime = newTime;

    accumulator += frameTime / projectProperties->GetMillisecondsPerTick();

    static ScriptEntitySystem *scriptEntitySystem = (ScriptEntitySystem*) GD::GetContainer()->entitySystemManager->GetEntitySystem<ScriptEntitySystem>();

    while (accumulator >= PHYSICS_DELTA_TIME) {
        time += PHYSICS_DELTA_TIME;
        accumulator -= PHYSICS_DELTA_TIME;
        scriptEntitySystem->PhysicsProcess(PHYSICS_DELTA_TIME);
        inputManager->ClearInputFlags();
    }

    const double alpha = accumulator / PHYSICS_DELTA_TIME;
}

void Game::VariableTimeStep(Uint32 lastFrameTime) {
    // Variable time step
    float variableDeltaTime = (SDL_GetTicks() - lastFrameTime) / projectProperties->GetMillisecondsPerTick();
    variableDeltaTime = (variableDeltaTime > projectProperties->GetMaxDeltaTime()) ? projectProperties->GetMaxDeltaTime() : variableDeltaTime;
}

void Game::Render() {
    glClearColor(projectProperties->backgroundDrawColor.r,
                 projectProperties->backgroundDrawColor.g,
                 projectProperties->backgroundDrawColor.b,
                 projectProperties->backgroundDrawColor.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    static SpriteRenderingEntitySystem *spriteRenderingEntitySystem = (SpriteRenderingEntitySystem*) GD::GetContainer()->entitySystemManager->GetEntitySystem<SpriteRenderingEntitySystem>();
    spriteRenderingEntitySystem->Render();

    static AnimatedSpriteRenderingEntitySystem *animatedSpriteRenderingEntitySystem = (AnimatedSpriteRenderingEntitySystem*) GD::GetContainer()->entitySystemManager->GetEntitySystem<AnimatedSpriteRenderingEntitySystem>();
    animatedSpriteRenderingEntitySystem->Render();

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
    logger->Debug("Roll Back Engine stopped!");
}
