#include "game.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include "global_dependencies.h"

#include "ecs/entity/system/sprite_rendering_entity_system.h"
#include "ecs/entity/system/animated_sprite_rendering_entity_system.h"
#include "ecs/entity/system/text_rendering_entity_system.h"
#include "ecs/entity/system/script_entity_system.h"
#include "ecs/entity/system/collision_entity_system.h"

#include "ecs/component/components/animated_sprite_component.h"
#include "ecs/component/components/text_label_component.h"
#include "ecs/component/components/scriptable_class_component.h"

#include "scripting/python/python_script_context.h"
#include "ecs/entity/system/timer_entity_system.h"
#include "rendering/renderer3d.h"

Game::Game() {
    logger = Logger::GetInstance();
    logger->SetLogLevel(LogLevel_DEBUG);
    projectProperties = ProjectProperties::GetInstance();
    engineContext = GD::GetContainer()->engineContext;
    renderContext = GD::GetContainer()->renderContext;
    renderer = GD::GetContainer()->renderer;
    renderer3D = GD::GetContainer()->renderer3D;
    inputManager = InputManager::GetInstance();
    networkContext = GD::GetContainer()->networkContext;
}

void Game::Initialize(int argv, char** args) {
    logger->SetLogLevel(LogLevel_ERROR);
    logger->Info("Seika Engine v" + engineContext->GetEngineVersion() + " started!");
    CommandLineFlagResult commandLineFlagResult = commandLineFlagHelper.ProcessCommandLineArgs(argv, args);
    projectProperties->LoadProjectConfigurations(commandLineFlagResult.workingDirectoryOverride + commandLineFlagResult.projectFilePath);
    InitializeSDL();
    InitializeRendering();
    AssetManager *assetManager = GD::GetContainer()->assetManager;
    assetManager->LoadEngineAssets();
    inputManager->LoadProjectInputActions();
    if (!commandLineFlagResult.workingDirectoryOverride.empty()) {
        FileHelper::ChangeDirectory(commandLineFlagResult.workingDirectoryOverride);
        logger->Debug("Set project root override to " + commandLineFlagResult.workingDirectoryOverride);
    }
    assetManager->LoadProjectAssets();
    InitializeECS();
    engineContext->SetRunning(true);
    engineContext->StartFPSCounter();
}

void Game::InitializeSDL() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        logger->Error("Error on initializing SDL\n" + std::string(SDL_GetError()));
        return;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        logger->Error("SDL_mixer could not initialized!");
        return;
    }
}

void Game::InitializeECS() {
    EntityComponentOrchestrator *entityComponentOrchestrator = GD::GetContainer()->entityComponentOrchestrator;
    // Components
    entityComponentOrchestrator->RegisterComponent<NodeComponent>();
    entityComponentOrchestrator->RegisterComponent<TimerComponent>();
    entityComponentOrchestrator->RegisterComponent<Transform2DComponent>();
    entityComponentOrchestrator->RegisterComponent<SpriteComponent>();
    entityComponentOrchestrator->RegisterComponent<AnimatedSpriteComponent>();
    entityComponentOrchestrator->RegisterComponent<TextLabelComponent>();
    entityComponentOrchestrator->RegisterComponent<ScriptableClassComponent>();
    entityComponentOrchestrator->RegisterComponent<ColliderComponent>();

    // Systems
    entityComponentOrchestrator->RegisterSystem<TimerEntitySystem>();
    ComponentSignature timerSystemSignature;
    timerSystemSignature.set(entityComponentOrchestrator->GetComponentType<TimerComponent>(), true);
    entityComponentOrchestrator->SetSystemSignature<TimerEntitySystem>(timerSystemSignature);

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

    entityComponentOrchestrator->RegisterSystem<CollisionEntitySystem>();
    ComponentSignature collisionSystemSignature;
    collisionSystemSignature.set(entityComponentOrchestrator->GetComponentType<ColliderComponent>());
    entityComponentOrchestrator->SetSystemSignature<CollisionEntitySystem>(collisionSystemSignature);

    entityComponentOrchestrator->InitializeAllSystems();

    // Load initial scene
    entityComponentOrchestrator->PrepareSceneChange(projectProperties->initialScenePath);
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

    renderer3D->Initialize();
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
    static EntityComponentOrchestrator *entityComponentOrchestrator = GD::GetContainer()->entityComponentOrchestrator;

    // Sleep until FRAME_TARGET_TIME has elapsed since last frame
    static Uint32 lastFrameTime = 0;
    const unsigned int FRAME_TARGET_TIME = projectProperties->GetMillisecondsPerTick() / projectProperties->GetTargetFPS();
    unsigned int timeToWait = FRAME_TARGET_TIME - (SDL_GetTicks() - lastFrameTime);
    if (timeToWait > 0 && timeToWait <= FRAME_TARGET_TIME) {
        SDL_Delay(timeToWait);
    }

    engineContext->UpdateFPSCounter();

    networkContext->Poll();

    FixedTimeStep();

    VariableTimeStep(lastFrameTime);

    // Remove Entities
    if (entityComponentOrchestrator->ShouldRemoveCurrentSceneAtEndOfUpdate()) {
        entityComponentOrchestrator->DestroyCurrentScene();
    }

    entityComponentOrchestrator->DestroyQueuedEntities();

    // Change Scene
    if (entityComponentOrchestrator->HasSceneToSwitchTo()) {
        CameraManager *cameraManager = GD::GetContainer()->cameraManager;
        Camera2D currentCamera = cameraManager->GetCurrentCamera2D();
        currentCamera.viewport = Vector2(0.0f, 0.0f);
        cameraManager->UpdateCurrentCamera2D(currentCamera);
        entityComponentOrchestrator->ChangeSceneTo();
    }

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

        // Check Collisions
        // TODO: Refactor collision system
//        static CollisionEntitySystem *collisionEntitySystem = (CollisionEntitySystem*) GD::GetContainer()->entitySystemManager->GetEntitySystem<CollisionEntitySystem>();
//        collisionEntitySystem->ProcessCollisions();

        scriptEntitySystem->PhysicsProcess(PHYSICS_DELTA_TIME);

        static TimerEntitySystem *timerEntitySystem = (TimerEntitySystem*) GD::GetContainer()->entitySystemManager->GetEntitySystem<TimerEntitySystem>();
        timerEntitySystem->Tick();

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

    if (projectProperties->areColliderVisible) {
        static CollisionEntitySystem *collisionEntitySystem = (CollisionEntitySystem*) GD::GetContainer()->entitySystemManager->GetEntitySystem<CollisionEntitySystem>();
        collisionEntitySystem->Render();
    }

    renderer->FlushBatches();

    // Temp 3D Test TODO: Finish implementing 3D renderer
    static AssetManager *assetManager = GD::GetContainer()->assetManager;
    // Texture Cubes
    static Texture *diffuseMap = assetManager->GetTexture("assets/container2.png");
    static Texture *specularMap = assetManager->GetTexture("assets/container2_specular.png");

    static Vector3 textureCubePositions[10] = {Vector3(0.0f, 0.0f, 0.0f),
                                               Vector3(2.0f, 5.0f, -15.0f),
                                               Vector3(-1.5f, -2.2f, -2.5f),
                                               Vector3(-3.8f, -2.0f, -12.3f),
                                               Vector3(-2.4f, -0.4f, -3.5f),
                                               Vector3(-1.7f, 3.0f, -7.5f),
                                               Vector3(1.3f, -2.0f, -2.5f),
                                               Vector3(1.5f, 2.0f, -2.5f),
                                               Vector3(1.5f, 0.2f, -1.5f),
                                               Vector3(-1.3f, 1.0f, -1.5f)
                                              };
    for (int i = 0; i < 10; i++) {
        renderer3D->AddTextureCubeDrawBatch(TextureCubeDrawBatch{
            .position = textureCubePositions[i],
            .scale = Vector3(1.0f),
            .rotationAngleInDegrees = i * 20.0f,
            .rotationAxisInDegrees = Vector3(1.0f, 0.3f, 0.5f),
            .diffuseMap = diffuseMap,
            .specularMap = specularMap,
            .shininess = 32.0f
        });
    }

    // Point Lights
    static Vector3 pointLightPositions[4] = {Vector3(0.7f, 0.2f, 2.0f),
                                             Vector3(2.3f, -3.3f, -4.0f),
                                             Vector3(-4.0f, 2.0f, -12.5f),
                                             Vector3(0.0f, 0.0f, -3.0f)
                                            };
    for (int i = 0; i < 4; i++) {
        renderer3D->AddPointLightDrawBatch(
        PointLightDrawBatch{
            .position = pointLightPositions[i],
            .scale = Vector3(0.2f)
        });
    }

    renderer3D->Render(GD::GetContainer()->cameraManager);

    SDL_GL_SwapWindow(renderContext->window);
}

bool Game::IsRunning() {
    return engineContext->IsRunning();
}

void Game::Destroy() {
    SDL_GL_DeleteContext(renderContext->gl_context);
    SDL_DestroyWindow(renderContext->window);
    SDL_Quit();
    logger->Info("Seika Engine stopped!");
}
