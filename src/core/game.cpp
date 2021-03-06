#include "game.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include "global_dependencies.h"

#include "ecs/system/systems/sprite_rendering_entity_system.h"
#include "ecs/system/systems/animated_sprite_rendering_entity_system.h"
#include "ecs/system/systems/text_rendering_entity_system.h"
#include "ecs/system/systems/collision_entity_system.h"
#include "ecs/system/systems/texture_cube_rendering_entity_system.h"

#include "scripting/python/python_script_context.h"
#include "ecs/system/systems/timer_entity_system.h"
#include "ecs/system/systems/directional_light_rendering_entity_system.h"
#include "ecs/system/systems/point_light_rendering_entity_system.h"
#include "ecs/system/systems/spot_light_rendering_entity_system.h"
#include "ecs/component/components/texture_cube_component.h"

Game::Game(int argv, char** args) {
    logger = Logger::GetInstance();
    projectProperties = ProjectProperties::GetInstance();
    engineContext = GD::GetContainer()->engineContext;
    renderContext = GD::GetContainer()->renderContext;
    audioContext = AudioContext::GetInstance();
    renderer2D = GD::GetContainer()->renderer2D;
    renderer3D = GD::GetContainer()->renderer3D;
    inputManager = InputManager::GetInstance();
    networkContext = GD::GetContainer()->networkContext;
    Initialize(argv, args);
}

Game::~Game() {
    Destroy();
}

void Game::Initialize(int argv, char** args) {
    logger->SetLogLevel(LogLevel_ERROR);
    CommandLineFlagResult commandLineFlagResult = commandLineFlagHelper.ProcessCommandLineArgs(argv, args);
    projectProperties->assetArchivePath = commandLineFlagResult.gameArchiveFileName;
    InitializeSDL();
    InitializeAudio();
    AssetManager *assetManager = GD::GetContainer()->assetManager;
    if (commandLineFlagResult.localAssets) {
        projectProperties->LoadProjectConfigurationsFromFile(commandLineFlagResult.workingDirectoryOverride + commandLineFlagResult.projectFilePath);
        InitializeRendering();
        assetManager->LoadEngineAssets();
        inputManager->LoadProjectInputActions();
        engineContext->GetEngineVersion(projectProperties->IsAssetsInMemory()); // Set engine version before directory change
    }
    if (!commandLineFlagResult.workingDirectoryOverride.empty()) {
        FileHelper::ChangeDirectory(commandLineFlagResult.workingDirectoryOverride);
        logger->Debug("Set project root override to " + commandLineFlagResult.workingDirectoryOverride);
    }
    if (!commandLineFlagResult.localAssets) {
        if (!FileHelper::DoesFileExist(projectProperties->assetArchivePath)) {
            logger->Error("Asset archive .pck not found!  Aborting...");
            return;
        }
        ArchiveLoader::GetInstance()->ReadArchive(projectProperties->assetArchivePath);
        logger->Debug("Reading asset pack '" + projectProperties->assetArchivePath + "' into memory.");
        ArchiveLoader::GetInstance()->PrintArchiveContents();
        projectProperties->LoadProjectConfigurationsFromMemory(commandLineFlagResult.projectFilePath);
        InitializeRendering();
        inputManager->LoadProjectInputActions();
        assetManager->LoadEngineAssets();
    }
    assetManager->LoadProjectAssets();
    InitializeECS();
    logger->Info("Seika Engine v" + engineContext->GetEngineVersion(projectProperties->IsAssetsInMemory()) + " started!");
    logger->Debug("Current Working Directory: " + FileHelper::GetCurentDirectory());
    engineContext->SetRunning(true);
    engineContext->StartFPSCounter();
}

void Game::Destroy() {
    SDL_GL_DeleteContext(renderContext->gl_context);
    SDL_DestroyWindow(renderContext->window);
    SDL_Quit();
    audioContext->ShutDown();
    logger->Info("Seika Engine stopped!");
}

void Game::InitializeSDL() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        logger->Error("Error on initializing SDL\n" + std::string(SDL_GetError()));
        return;
    }
}

void Game::InitializeAudio() {
    // TODO: Will eventually deprecate the SDL_mixer api
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        logger->Error("SDL_mixer could not initialized!");
        return;
    }

    if (!audioContext->Initialize()) {
        logger->Error("Error initializing audio context!");
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
    entityComponentOrchestrator->RegisterComponent<Transform3DComponent>();
    entityComponentOrchestrator->RegisterComponent<MaterialComponent>();
    entityComponentOrchestrator->RegisterComponent<TextureCubeComponent>();
    entityComponentOrchestrator->RegisterComponent<DirectionalLightComponent>();
    entityComponentOrchestrator->RegisterComponent<PointLightComponent>();
    entityComponentOrchestrator->RegisterComponent<SpotLightComponent>();

    // Systems
    entityComponentOrchestrator->RegisterSystem<TimerEntitySystem>(EntitySystemHook::PHYSICS_PROCESS);
    ComponentSignature timerSystemSignature;
    timerSystemSignature.set(entityComponentOrchestrator->GetComponentType<TimerComponent>(), true);
    entityComponentOrchestrator->SetSystemSignature<TimerEntitySystem>(timerSystemSignature);

    entityComponentOrchestrator->RegisterSystem<SpriteRenderingEntitySystem>(EntitySystemHook::RENDER);
    ComponentSignature spriteRenderingSystemSignature;
    spriteRenderingSystemSignature.set(entityComponentOrchestrator->GetComponentType<Transform2DComponent>(), true);
    spriteRenderingSystemSignature.set(entityComponentOrchestrator->GetComponentType<SpriteComponent>(), true);
    entityComponentOrchestrator->SetSystemSignature<SpriteRenderingEntitySystem>(spriteRenderingSystemSignature);

    entityComponentOrchestrator->RegisterSystem<AnimatedSpriteRenderingEntitySystem>(EntitySystemHook::RENDER);
    ComponentSignature animatedSpriteRenderingSystemSignature;
    animatedSpriteRenderingSystemSignature.set(entityComponentOrchestrator->GetComponentType<Transform2DComponent>(), true);
    animatedSpriteRenderingSystemSignature.set(entityComponentOrchestrator->GetComponentType<AnimatedSpriteComponent>(), true);
    entityComponentOrchestrator->SetSystemSignature<AnimatedSpriteRenderingEntitySystem>(animatedSpriteRenderingSystemSignature);

    entityComponentOrchestrator->RegisterSystem<TextRenderingEntitySystem>(EntitySystemHook::RENDER);
    ComponentSignature textRenderingSystemSignature;
    textRenderingSystemSignature.set(entityComponentOrchestrator->GetComponentType<Transform2DComponent>(), true);
    textRenderingSystemSignature.set(entityComponentOrchestrator->GetComponentType<TextLabelComponent>(), true);
    entityComponentOrchestrator->SetSystemSignature<TextRenderingEntitySystem>(textRenderingSystemSignature);

    ScriptEntitySystem *scriptEntitySystem = entityComponentOrchestrator->RegisterSystem<ScriptEntitySystem>(EntitySystemHook::PROCESS | EntitySystemHook::PHYSICS_PROCESS);
    scriptEntitySystem->InstallScriptContext<PythonScriptContext>();
    ComponentSignature scriptSystemSignature;
    scriptSystemSignature.set(entityComponentOrchestrator->GetComponentType<ScriptableClassComponent>(), true);
    entityComponentOrchestrator->SetSystemSignature<ScriptEntitySystem>(scriptSystemSignature);

    EntitySystemHook collisionSystemHooks = projectProperties->areColliderVisible ? EntitySystemHook::RENDER | EntitySystemHook::ON_ENTITY_TAGS_UPDATE : EntitySystemHook::ON_ENTITY_TAGS_UPDATE;
    entityComponentOrchestrator->RegisterSystem<CollisionEntitySystem>(collisionSystemHooks);
    ComponentSignature collisionSystemSignature;
    collisionSystemSignature.set(entityComponentOrchestrator->GetComponentType<ColliderComponent>(), true);
    entityComponentOrchestrator->SetSystemSignature<CollisionEntitySystem>(collisionSystemSignature);

    entityComponentOrchestrator->RegisterSystem<TextureCubeRenderingEntitySystem>(EntitySystemHook::RENDER);
    ComponentSignature textureCubeRenderingSystemSignature;
    textureCubeRenderingSystemSignature.set(entityComponentOrchestrator->GetComponentType<Transform3DComponent>(), true);
    textureCubeRenderingSystemSignature.set(entityComponentOrchestrator->GetComponentType<MaterialComponent>(), true);
    textureCubeRenderingSystemSignature.set(entityComponentOrchestrator->GetComponentType<TextureCubeComponent>(), true);
    entityComponentOrchestrator->SetSystemSignature<TextureCubeRenderingEntitySystem>(textureCubeRenderingSystemSignature);

    entityComponentOrchestrator->RegisterSystem<DirectionalLightRenderingEntitySystem>(EntitySystemHook::RENDER);
    ComponentSignature directionalLightRenderingSystemSignature;
    directionalLightRenderingSystemSignature.set(entityComponentOrchestrator->GetComponentType<Transform3DComponent>(), true);
    directionalLightRenderingSystemSignature.set(entityComponentOrchestrator->GetComponentType<MaterialComponent>(), true);
    directionalLightRenderingSystemSignature.set(entityComponentOrchestrator->GetComponentType<DirectionalLightComponent>(), true);
    entityComponentOrchestrator->SetSystemSignature<DirectionalLightRenderingEntitySystem>(directionalLightRenderingSystemSignature);

    entityComponentOrchestrator->RegisterSystem<PointLightRenderingEntitySystem>(EntitySystemHook::RENDER);
    ComponentSignature pointLightRenderingSystemSignature;
    pointLightRenderingSystemSignature.set(entityComponentOrchestrator->GetComponentType<Transform3DComponent>(), true);
    pointLightRenderingSystemSignature.set(entityComponentOrchestrator->GetComponentType<MaterialComponent>(), true);
    pointLightRenderingSystemSignature.set(entityComponentOrchestrator->GetComponentType<PointLightComponent>(), true);
    entityComponentOrchestrator->SetSystemSignature<PointLightRenderingEntitySystem>(pointLightRenderingSystemSignature);

    entityComponentOrchestrator->RegisterSystem<SpotLightRenderingEntitySystem>(EntitySystemHook::RENDER);
    ComponentSignature spotLightRenderingSystemSignature;
    spotLightRenderingSystemSignature.set(entityComponentOrchestrator->GetComponentType<Transform3DComponent>(), true);
    spotLightRenderingSystemSignature.set(entityComponentOrchestrator->GetComponentType<MaterialComponent>(), true);
    spotLightRenderingSystemSignature.set(entityComponentOrchestrator->GetComponentType<SpotLightComponent>(), true);
    entityComponentOrchestrator->SetSystemSignature<SpotLightRenderingEntitySystem>(spotLightRenderingSystemSignature);

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
                                projectProperties->intitialWindowWidth,
                                projectProperties->intitialWindowHeight,
                                renderContext->windowFlags);
    renderContext->gl_context = SDL_GL_CreateContext(renderContext->window);
    renderContext->currentWindowWidth = projectProperties->intitialWindowWidth;
    renderContext->currentWindowHeight = projectProperties->intitialWindowHeight;

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        logger->Error("Couldn't initialize glad");
    }

    renderContext->InitializeFont();

    renderer2D->Initialize();

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
                renderContext->currentWindowWidth = event.window.data1;
                renderContext->currentWindowHeight = event.window.data2;
                renderer2D->UpdateProjection();
                // TODO: Update 3D Renderer
                glViewport(0, 0, renderContext->currentWindowWidth, renderContext->currentWindowHeight);
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

    const float variableDeltaTime = (SDL_GetTicks() - lastFrameTime) / projectProperties->GetMillisecondsPerTick();
    static EntitySystemManager* entitySystemManager = EntitySystemManager::GetInstance();
    entitySystemManager->ProcessSystemsHook(variableDeltaTime);

    PhysicsUpdate();

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
        entityComponentOrchestrator->ChangeSceneTo(projectProperties->IsAssetsInMemory());
    }

    lastFrameTime = SDL_GetTicks();
}

void Game::PhysicsUpdate() {
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

    static EntitySystemManager* entitySystemManager = EntitySystemManager::GetInstance();

    while (accumulator >= PHYSICS_DELTA_TIME) {
        time += PHYSICS_DELTA_TIME;
        accumulator -= PHYSICS_DELTA_TIME;

        entitySystemManager->PhysicsProcessSystemsHook(PHYSICS_DELTA_TIME);

        inputManager->ClearInputFlags();
    }
}

void Game::Render() {
    glClearColor(projectProperties->backgroundDrawColor.r,
                 projectProperties->backgroundDrawColor.g,
                 projectProperties->backgroundDrawColor.b,
                 projectProperties->backgroundDrawColor.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    static EntitySystemManager* entitySystemManager = EntitySystemManager::GetInstance();
    entitySystemManager->RenderSystemsHook();

    renderer2D->FlushBatches();

    renderer3D->Render(GD::GetContainer()->cameraManager);

    SDL_GL_SwapWindow(renderContext->window);
}

bool Game::IsRunning() {
    return engineContext->IsRunning();
}
