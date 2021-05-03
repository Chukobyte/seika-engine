#ifndef PROJECT_PROPERTIES_H
#define PROJECT_PROPERTIES_H

#include <string>

#include "color.h"

class ProjectProperties {
  private:
    static ProjectProperties *instance;
    unsigned int targetFPS = 60;
    double millisecondsPerTick = 1000.0f;
    double maxDeltaTime = 0.5f;
    double fixedPhysicsDeltaTime = 0.01f;

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

    double GetMillisecondsPerTick() {
        return millisecondsPerTick;
    }

    double GetMaxDeltaTime() {
        return maxDeltaTime;
    }

    double GetFixedPhysicsDeltaTime() {
        return fixedPhysicsDeltaTime;
    }
};

#endif //PROJECT_PROPERTIES_H
