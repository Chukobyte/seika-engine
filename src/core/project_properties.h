#ifndef PROJECT_PROPERTIES_H
#define PROJECT_PROPERTIES_H

#include "color.h"

struct ProjectProperties {
    std::string gameTitle = "Roll Back Engine";
    int windowWidth = 800;
    int windowHeight = 600;
    Color backgroundDrawColor = Color(20.f / 255.0f, 20.f / 255.0f, 20.f / 255.0f);
};

#endif //PROJECT_PROPERTIES_H
