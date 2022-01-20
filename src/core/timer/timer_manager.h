#pragma once

#include "../utils/singleton.h"

#include <map>

#include "../ecs/entity/entity.h"
#include "timer.h"
#include "../ecs/component/components/timer_component.h"
#include "../ecs/component/component_manager.h"
#include "../project_properties.h"

class TimerManager : public Singleton<TimerManager> {
  private:
    ProjectProperties *projectProperties = nullptr;

  public:
    std::map<Entity, Timer*> timers;
    std::map<Entity, Timer*> activeTimers;

    TimerManager(singleton);
    void Initialize();
    Timer* GenerateTimer(Entity entity, Uint32 waitTimeInMilliseconds, bool loops);
    bool HasTimer(Entity entity);
    bool HasActiveTimer(Entity entity);
    void RemoveTimer(Entity entity);
    void StartTimer(Entity entity);
    void StopTimer(Entity entity);
    void PauseTimer(Entity entity);
    void ResumeTimer(Entity entity);
    float GetTimerWaitTime(Entity entity);
    void SetTimerWaitTime(Entity entity, float waitTime);
    float GetTimerTimeLeft(Entity entity);
    bool IsTimerStopped(Entity entity);
    bool IsTimerPaused(Entity entity);
    bool DoesTimerLoop(Entity entity);
    void SetTimerLoops(Entity entity, bool loops);
};
