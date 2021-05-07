#include "global_dependencies.h"

GD* GD::instance = 0;

GD::GD() {
    ResetDependencies();
}

GD* GD::GetContainer() {
    if(!instance) {
        instance = new GD();
    }
    return instance;
}

void GD::ResetDependencies() {
    delete engineContext;
    delete renderContext;
    delete collisionContext;
    delete renderer;
    delete assetManager;
    delete entityManager;
    delete entitySystemManager;
    delete componentManager;
    delete sceneManager;
    delete entityComponentOrchestrator;
    delete cameraManager;
    engineContext = new EngineContext();
    renderContext = new RenderContext();
    collisionContext = new CollisionContext();
    renderer = new Renderer();
    assetManager = new AssetManager();
    entityManager = new EntityManager();
    entitySystemManager = new EntitySystemManager();
    componentManager = new ComponentManager();
    sceneManager = new SceneManager(entityManager, componentManager, assetManager);
    entityComponentOrchestrator = new EntityComponentOrchestrator(entityManager, entitySystemManager, componentManager, sceneManager);
    cameraManager = new CameraManager();
}
