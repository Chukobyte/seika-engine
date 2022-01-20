#include "global_dependencies.h"
#include "ecs/system/entity_system_manager.h"

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
    delete renderer2D;
    delete renderer3D;
    delete assetManager;
    delete entityManager;
    delete componentManager;
    delete sceneContext;
    delete sceneManager;
    delete entityComponentOrchestrator;
    delete cameraManager;
    delete networkConnectionContext;
    delete networkContext;
    engineContext = new EngineContext();
    renderContext = new RenderContext();
    collisionContext = new CollisionContext();
    renderer2D = new Renderer2D(renderContext);
    renderer3D = new Renderer3D();
    assetManager = AssetManager::GetInstance();
    entityManager = new EntityManager();
    componentManager = new ComponentManager();
    sceneContext = new SceneContext();
    sceneManager = new SceneManager(sceneContext, entityManager, componentManager, assetManager);
    entityComponentOrchestrator = new EntityComponentOrchestrator(entityManager, EntitySystemManager::GetInstance(), componentManager, sceneManager);
    cameraManager = new CameraManager();
    networkConnectionContext = new NetworkConnectionContext();
    networkContext = new NetworkContext();
}
