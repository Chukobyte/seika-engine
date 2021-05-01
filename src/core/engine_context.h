#ifndef ENGINE_CONTEXT_H
#define ENGINE_CONTEXT_H

#include <string>

class EngineContext {
  private:
    bool running = false;

  public:
    void SetRunning(bool value);
    bool IsRunning() const;
    std::string GetEngineVersion() const;
};

#endif //ENGINE_CONTEXT_H
