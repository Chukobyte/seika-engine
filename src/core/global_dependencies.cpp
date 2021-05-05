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
    delete renderer;
    delete assetManager;
    delete entityManager;
    delete entitySystemManager;
    delete componentManager;
    delete cameraManager;
    engineContext = new EngineContext();
    renderContext = new RenderContext();
    renderer = new Renderer();
    assetManager = new AssetManager();
    entityManager = new EntityManager();
    entitySystemManager = new EntitySystemManager();
    componentManager = new ComponentManager();
    entityComponentOrchestrator = new EntityComponentOrchestrator(entityManager, entitySystemManager, componentManager);
    cameraManager = new CameraManager();
}
