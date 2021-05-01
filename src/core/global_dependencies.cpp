#include "global_dependencies.h"

GD* GD::instance = 0;

GD::GD() {
    engineContext = new EngineContext();
    renderContext = new RenderContext();
}

GD* GD::GetContainer() {
    if(!instance) {
        instance = new GD();
    }
    return instance;
}
