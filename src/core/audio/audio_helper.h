#ifndef AUDIO_HELPER_H
#define AUDIO_HELPER_H

#include "../global_dependencies.h"

class AudioHelper {
  public:
    static void PlayMusic(const std::string &musicId) {
        static AssetManager *assetManager = GD::GetContainer()->assetManager;
        Mix_PlayMusic(assetManager->GetMusic(musicId), -1);
    }

    static void StopMusic() {
        Mix_HaltMusic();
    }

    static void PauseMusic() {
        Mix_PauseMusic();
    }

    static void PlaySound(const std::string &soundId) {
        static AssetManager *assetManager = GD::GetContainer()->assetManager;
        Mix_PlayChannel(-1, assetManager->GetSound(soundId), 0);
    }

    static void SetMusicVolume(int volume) {
        Mix_VolumeMusic(volume);
    }

    static void SetSoundVolume(int volume) {
        static AssetManager *assetManager = GD::GetContainer()->assetManager;
        for (auto const &pair : assetManager->GetAllSounds()) {
            Mix_Chunk *soundChunk = pair.second;
            Mix_VolumeChunk(soundChunk, volume);
        }
    }

    static void SetAllVolume(int volume) {
        SetMusicVolume(volume);
        SetSoundVolume(volume);
    }
};


#endif //AUDIO_HELPER_H
