#ifndef TIMER_MANAGER_H
#define TIMER_MANAGER_H

#include <map>

#include "../ecs/entity/entity.h"
#include "timer.h"
#include "../ecs/component/components/timer_component.h"
#include "../ecs/component/component_manager.h"
#include "../project_properties.h"

class TimerManager {
  private:
    static TimerManager *instance;
    ComponentManager *componentManager = nullptr;
    ProjectProperties *projectProperties = nullptr;

    TimerManager() {}
  public:
    std::map<Entity, Timer*> timers;
    std::map<Entity, Timer*> activeTimers;

    static TimerManager* GetInstance() {
        if (!instance) {
            instance = new TimerManager();
        }
        return instance;
    }

    void Initialize(ComponentManager *componentManager) {
        this->componentManager = componentManager;
        projectProperties = ProjectProperties::GetInstance();
    }

    Timer* GenerateTimer(Entity entity, Uint32 waitTimeInMilliseconds, bool loops) {
        if (timers.count(entity) <= 0) {
            timers.emplace(entity, new Timer(waitTimeInMilliseconds, loops));
        }
        return timers[entity];
    }

    bool HasTimer(Entity entity) {
        return timers.count(entity) > 0;
    }

    bool HasActiveTimer(Entity entity) {
        return activeTimers.count(entity) > 0;
    }

    void RemoveTimer(Entity entity) {
        if (HasTimer(entity)) {
            activeTimers.erase(entity);
            timers[entity]->Stop();
            timers.erase(entity);

            TimerComponent timerComponent = componentManager->GetComponent<TimerComponent>(entity);
            delete timerComponent.timer;
        }
    }

    void StartTimer(Entity entity) {
        if (HasActiveTimer(entity)) {
            TimerComponent timerComponent = componentManager->GetComponent<TimerComponent>(entity);
            activeTimers.emplace(entity, timerComponent.timer);
        }
        activeTimers[entity]->Start();
    }

    void StopTimer(Entity entity) {
        if (HasActiveTimer(entity)) {
            activeTimers[entity]->Stop();
            activeTimers.erase(entity);
        }
    }

    void PauseTimer(Entity entity) {
        if (HasActiveTimer(entity)) {
            activeTimers[entity]->Pause();
        }
    }

    void ResumeTimer(Entity entity) {
        if (HasActiveTimer(entity)) {
            activeTimers[entity]->UnPause();
        }
    }

    float GetTimerWaitTime(Entity entity) {
        if (HasActiveTimer(entity)) {
            activeTimers[entity]->GetWaitTime() / projectProperties->GetMillisecondsPerTick();
        }
        return 0.0f;
    }

    void SetTimerWaitTime(Entity entity, float waitTime) {
        if (HasActiveTimer(entity)) {
            Uint32 waitTimeInMilliSeconds = waitTime * projectProperties->GetMillisecondsPerTick();
            activeTimers[entity]->SetWaitTime(waitTimeInMilliSeconds);
        }
    }

    bool IsTimerStopped(Entity entity) {
        if (HasActiveTimer(entity)) {
            return activeTimers[entity]->HasStopped();
        }
        return true;
    }

    bool IsTimerPaused(Entity entity) {
        if (HasActiveTimer(entity)) {
            return activeTimers[entity]->IsPaused();
        }
        return true;
    }

    bool DoesTimerLoop(Entity entity) {
        if (HasActiveTimer(entity)) {
            return activeTimers[entity]->DoesLoop();
        }
        return false;
    }

    void SetTimerLoops(Entity entity, bool loops) {
        if (HasActiveTimer(entity)) {
            activeTimers[entity]->SetLoop(loops);
        }
    }
};

#endif //TIMER_MANAGER_H
