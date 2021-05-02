#ifndef TIMER_MANAGER_H
#define TIMER_MANAGER_H

#include <map>

#include "../ecs/entity/entity.h"
#include "timer.h"
#include "../ecs/component/components/timer_component.h"
#include "../ecs/component/component_manager.h"

class TimerManager {
  private:
    static TimerManager *instance;
    ComponentManager *componentManager = nullptr;

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
    }

    Timer* GenerateTimer(Entity entity, Uint32 waitTimeInMilliseconds, bool loops) {
        if (timers.count(entity) <= 0) {
            timers.emplace(entity, new Timer(waitTimeInMilliseconds, loops));
        }
        return timers[entity];
    }

    void RemoveTimer(Entity entity) {
        if (timers.count(entity) > 0) {
            activeTimers.erase(entity);
            timers[entity]->Stop();
            timers.erase(entity);

            TimerComponent timerComponent = componentManager->GetComponent<TimerComponent>(entity);
            delete timerComponent.timer;
        }
    }
};

#endif //TIMER_MANAGER_H
