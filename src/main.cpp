//#include "core/game.h"
#include "core/audio/audio_file_helper.h"
#include "core/audio/audio_context.h"

static void OpenALTest() {
    AudioContext *audioContext = AudioContext::GetInstance();
    if (!audioContext->Initialize()) {
        std::cerr << "Error initializing audio context!" << std::endl;
        return;
    }

//    AudioFileData *audioFileData = AudioFileHelper::LoadWav("assets/audio/music/test_music.wav", true);
    AudioFileData *audioFileData = AudioFileHelper::LoadWav("assets/audio/music/test_song_that_works_when_looping.wav", true);
    audioFileData->Play();
    while (audioFileData->IsPlaying()) {}

    audioFileData->Destroy();

    audioContext->ShutDown();
}

int main(int argv, char** args) {
//    Game gameEngine(argv, args);
//
//    while (gameEngine.IsRunning()) {
//        gameEngine.ProcessInput();
//        gameEngine.Update();
//        gameEngine.Render();
//    }

    OpenALTest();

    return 0;
}
