#ifndef GLOBAL_DEPENDENCIES_H
#define GLOBAL_DEPENDENCIES_H

#include "engine_context.h"
#include "rendering/render_context.h"

class GD {
    /* A singleton that holds global pointers...*/
  private:
    static GD *instance;

    GD();
  public:
    EngineContext *engineContext = nullptr;
    RenderContext *renderContext = nullptr;

    static GD* GetContainer();
};

#endif //GLOBAL_DEPENDENCIES_H
