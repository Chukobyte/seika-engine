#include "timer_manager.h"

TimerManager *TimerManager::instance = nullptr;

void TimerManager::Initialize() {
    projectProperties = ProjectProperties::GetInstance();
}

Timer* TimerManager::GenerateTimer(Entity entity, Uint32 waitTimeInMilliseconds, bool loops) {
    if (timers.count(entity) <= 0) {
        timers.emplace(entity, new Timer(waitTimeInMilliseconds, loops));
    }
    return timers[entity];
}

bool TimerManager::HasTimer(Entity entity) {
    return timers.count(entity) > 0;
}

bool TimerManager::HasActiveTimer(Entity entity) {
    return activeTimers.count(entity) > 0;
}

void TimerManager::RemoveTimer(Entity entity) {
    if (HasTimer(entity)) {
        activeTimers.erase(entity);
        timers[entity]->Stop();
        delete timers[entity];
        timers.erase(entity);
    }
}

void TimerManager::StartTimer(Entity entity) {
    if (!HasActiveTimer(entity)) {
        activeTimers.emplace(entity, timers[entity]);
    }
    activeTimers[entity]->Start();
}

void TimerManager::StopTimer(Entity entity) {
    if (HasActiveTimer(entity)) {
        activeTimers[entity]->Stop();
        activeTimers.erase(entity);
    }
}

void TimerManager::PauseTimer(Entity entity) {
    if (HasActiveTimer(entity)) {
        activeTimers[entity]->Pause();
    }
}

void TimerManager::ResumeTimer(Entity entity) {
    if (HasActiveTimer(entity)) {
        activeTimers[entity]->UnPause();
    }
}

float TimerManager::GetTimerWaitTime(Entity entity) {
    return timers[entity]->GetWaitTime() / projectProperties->GetMillisecondsPerTick();
}

void TimerManager::SetTimerWaitTime(Entity entity, float waitTime) {
    Uint32 waitTimeInMilliSeconds = waitTime * projectProperties->GetMillisecondsPerTick();
    timers[entity]->SetWaitTime(waitTimeInMilliSeconds);
}

float TimerManager::GetTimerTimeLeft(Entity entity) {
    return (timers[entity]->GetWaitTime() - timers[entity]->GetTicks()) / projectProperties->GetMillisecondsPerTick();
}

bool TimerManager::IsTimerStopped(Entity entity) {
    if (HasActiveTimer(entity)) {
        return activeTimers[entity]->HasStopped();
    }
    return true;
}

bool TimerManager::IsTimerPaused(Entity entity) {
    if (HasActiveTimer(entity)) {
        return activeTimers[entity]->IsPaused();
    }
    return false;
}

bool TimerManager::DoesTimerLoop(Entity entity) {
    return timers[entity]->DoesLoop();
}

void TimerManager::SetTimerLoops(Entity entity, bool loops) {
    timers[entity]->SetLoop(loops);
}
