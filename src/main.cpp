#include "core/game.h"
#include "core/audio/audio_file_helper.h"
#include "core/audio/audio_context.h"

int main(int argv, char** args) {
    Game gameEngine(argv, args);

    AudioContext *audioContext = AudioContext::GetInstance();
    if (!audioContext->Initialize()) {
        std::cerr << "Error initializing audio context!" << std::endl;
        return -1;
    }

    AudioFileData *audioFileData = AudioFileHelper::LoadWav("assets/audio/music/test_song_that_works_when_looping.wav", true);
    audioFileData->Play();

    while (gameEngine.IsRunning()) {
        gameEngine.ProcessInput();
        gameEngine.Update();
        gameEngine.Render();
    }

    audioFileData->Destroy();
    audioContext->ShutDown();

    return 0;
}
