#ifndef GLOBAL_DEPENDENCIES_H
#define GLOBAL_DEPENDENCIES_H

#include "engine_context.h"
#include "rendering/render_context.h"
#include "rendering/renderer.h"
#include "asset_manager.h"
#include "ecs/entity/entity_manager.h"
#include "ecs/entity/system/entity_system_manager.h"
#include "ecs/component/component_manager.h"
#include "scene/scene.h"
#include "ecs/entity_component_orchestrator.h"
#include "camera/camera_manager.h"

class GD {
    /* A singleton that holds global pointers...*/
  private:
    static GD *instance;

    GD();
  public:
    EngineContext *engineContext = nullptr;
    RenderContext *renderContext = nullptr;
    Renderer *renderer = nullptr;
    AssetManager *assetManager = nullptr;
    EntityManager *entityManager = nullptr;
    EntitySystemManager *entitySystemManager = nullptr;
    ComponentManager *componentManager = nullptr;
    SceneManager *sceneManager = nullptr;
    EntityComponentOrchestrator *entityComponentOrchestrator = nullptr;
    CameraManager *cameraManager = nullptr;

    static GD* GetContainer();

    void ResetDependencies();
};

#endif //GLOBAL_DEPENDENCIES_H
