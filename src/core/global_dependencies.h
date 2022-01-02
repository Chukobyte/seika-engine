#ifndef GLOBAL_DEPENDENCIES_H
#define GLOBAL_DEPENDENCIES_H

#include "engine_context.h"
#include "rendering/render_context.h"
#include "rendering/renderer2d.h"
#include "rendering/renderer3d.h"
#include "asset_manager.h"
#include "ecs/entity/entity_manager.h"
#include "ecs/component/component_manager.h"
#include "ecs/entity_component_orchestrator.h"
#include "physics/collision/collision_context.h"
#include "scene/scene.h"
#include "scene/scene_manager.h"
#include "scene/scene_context.h"
#include "camera/camera_manager.h"
#include "networking/network_connection_context.h"
#include "networking/network_context.h"

class EntityComponentOrchestrator;

class GD {
    /* A singleton that holds global pointers...*/
  private:
    static GD *instance;

    GD();
  public:
    EngineContext *engineContext = nullptr;
    RenderContext *renderContext = nullptr;
    CollisionContext *collisionContext = nullptr;
    Renderer2D *renderer2D = nullptr;
    Renderer3D *renderer3D = nullptr;
    AssetManager *assetManager = nullptr;
    EntityManager *entityManager = nullptr;
    ComponentManager *componentManager = nullptr;
    SceneManager *sceneManager = nullptr;
    SceneContext *sceneContext = nullptr;
    EntityComponentOrchestrator *entityComponentOrchestrator = nullptr;
    CameraManager *cameraManager = nullptr;
    NetworkConnectionContext *networkConnectionContext = nullptr;
    NetworkContext *networkContext = nullptr;

    static GD* GetContainer();

    void ResetDependencies();
};

#endif //GLOBAL_DEPENDENCIES_H
