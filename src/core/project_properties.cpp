#include "project_properties.h"

ProjectProperties* ProjectProperties::instance = 0;

ProjectProperties * ProjectProperties::GetInstance() {
    if (!instance) {
        instance = new ProjectProperties();
    }
    return instance;
}
