#ifndef PROJECT_PROPERTIES_H
#define PROJECT_PROPERTIES_H

#include <string>

#include "color.h"

class ProjectProperties {
  private:
    static ProjectProperties *instance;
    unsigned int targetFPS = 60;
    float millisecondsPerTick = 1000.0f;
    float maxDeltaTime = 0.5f;

    ProjectProperties() = default;
  public:
    std::string gameTitle = "Roll Back Engine";
    int windowWidth = 800;
    int windowHeight = 600;
    Color backgroundDrawColor = Color(20.f / 255.0f, 20.f / 255.0f, 20.f / 255.0f);

    static ProjectProperties* GetInstance();

    unsigned int GetTargetFPS() {
        return targetFPS;
    }

    float GetMillisecondsPerTick() {
        return millisecondsPerTick;
    }

    float GetMaxDeltaTime() {
        return maxDeltaTime;
    }
};

#endif //PROJECT_PROPERTIES_H
