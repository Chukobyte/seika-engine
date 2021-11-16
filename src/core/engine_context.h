#ifndef ENGINE_CONTEXT_H
#define ENGINE_CONTEXT_H

#include <string>

#include "timer/timer.h"

class FPSCounter {
  public:
    unsigned int countedFrames = 0;
    Timer* timer;
    long averageFPS = 0.0f;

    FPSCounter() {
        timer = new Timer(4294967294, true);
    }

    ~FPSCounter() {
        delete timer;
    }

    void Start() {
        timer->Start();
    }

    void Update() {
        countedFrames++;
        averageFPS = countedFrames / (timer->GetTicks() / 1000.f);
        if(averageFPS > 2000000) {
            averageFPS = 0;
        }
    }
};

class EngineContext {
  private:
    bool running = false;
    std::string engineVersion;
    FPSCounter fpsCounter;

  public:
    void SetRunning(bool value);

    bool IsRunning() const;

    std::string GetEngineVersion();

    void StartFPSCounter();

    void UpdateFPSCounter();

    long GetFPS() const;
};

#endif //ENGINE_CONTEXT_H
