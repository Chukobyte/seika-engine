#ifndef TIMER_ENTITY_SYSTEM_H
#define TIMER_ENTITY_SYSTEM_H

#include "../entity_system.h"
#include "../../../timer/timer_manager.h"
#include "../../../signal_manager.h"

class TimerEntitySystem : public EntitySystem {
  private:
    TimerManager *timerManager = nullptr;
    SignalManager *signalManager = nullptr;
  public:
    TimerEntitySystem() {
        timerManager = TimerManager::GetInstance();
        signalManager = SignalManager::GetInstance();
        enabled = true;
    }

    void Initialize() override {
        EntitySystem::Initialize();
        timerManager->Initialize();
    }

    void OnEntityDestroyed(Entity entity) override {
        EntitySystem::OnEntityDestroyed(entity);
        timerManager->RemoveTimer(entity);
    }

    // Tick
    void PhysicsProcess(float deltaTime) override {
        for (auto const &pair : timerManager->activeTimers) {
            Entity entity = pair.first;
            Timer *timer = pair.second;
            if (timer->HasReachedTimeOut()) {
                timer->Stop();
                // Emit signal
                signalManager->EmitSignal(entity, "timeout");
                if (timer->DoesLoop()) {
                    timer->Start();
                } else {
                    timerManager->activeTimers.erase(entity);
                }
            }
        }
    }
};

#endif //TIMER_ENTITY_SYSTEM_H
