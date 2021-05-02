#ifndef TIMER_H
#define TIMER_H

#include <SDL2/SDL.h>

class Timer {
  private:
    Uint32 waitTime;
    bool loops;
    Uint32 startTicks;
    Uint32 pausedTicks;
    bool isPaused;
    bool hasStarted;

  public:
    Timer(Uint32 waitTimeInMilliseconds, bool loops = false);
    Uint32 GetWaitTime() const;
    Uint32 GetTimeLeft() const;
    void SetWaitTime(Uint32 waitTimeInMilliseconds);
    bool DoesLoop() const;
    void SetLoop(bool loops);
    void Start();
    void Stop();
    void Pause();
    void UnPause();
    bool HasStopped() const;
    bool HasReachedTimeOut() const;
    Uint32 GetTicks() const;
    bool HasStarted() const;
    bool IsPaused() const;
};

#endif
