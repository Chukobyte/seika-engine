#ifndef GAME_H
#define GAME_H


class Game {
  public:
    void Initialize();

    void ProcessInput();

    void Update();

    void Render();

    bool IsRunning();

    void Destroy();
};


#endif //GAME_H
