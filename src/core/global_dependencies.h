#ifndef GLOBAL_DEPENDENCIES_H
#define GLOBAL_DEPENDENCIES_H

#include "engine_context.h"
#include "rendering/render_context.h"
#include "asset_manager.h"

class GD {
    /* A singleton that holds global pointers...*/
  private:
    static GD *instance;

    GD();
  public:
    EngineContext *engineContext = nullptr;
    RenderContext *renderContext = nullptr;
    AssetManager *assetManager = nullptr;

    static GD* GetContainer();

    void ResetDependencies();
};

#endif //GLOBAL_DEPENDENCIES_H
