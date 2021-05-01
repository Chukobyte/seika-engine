#include "global_dependencies.h"

GD* GD::instance = 0;

GD::GD() {
    engineContext = new EngineContext();
}

GD* GD::GetContainer() {
    if(!instance) {
        instance = new GD();
    }
    return instance;
}
