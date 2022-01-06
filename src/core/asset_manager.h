#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include <map>
#include <string>

#include <SDL2/SDL_mixer.h>

#include "rendering/texture.h"
#include "rendering/font.h"
#include "audio/audio_stream.h"
#include "project_properties.h"
#include "utils/archive_loader.h"

static const std::string &BLANK_WHITE_TEXTURE_ASSET_ID = "bt";
static const std::string &DEFAULT_FONT_ASSET_ID = "seika_default";
static const std::string &DEFAULT_FONT_ASSET_PATH = "assets/fonts/pine_type.ttf";
static const int DEFAULT_FONT_SIZE = 20;

class AssetManager {
  private:
    std::map<std::string, Texture*> textures;
    std::map<std::string, Font*> fonts;
    std::map<std::string, Mix_Music*> music;
    std::map<std::string, Mix_Chunk*> sounds;
    std::map<std::string, AudioStream*> audioStreams;

    ProjectProperties *projectProperties = nullptr;
    ArchiveLoader *archiveLoader = nullptr;
    Logger *logger = nullptr;

    Texture *LoadTextureFromFile(const TextureConfiguration &textureConfiguration);

    Texture *LoadTextureFromMemory(const TextureConfiguration &textureConfiguration);

    void LoadTexture(const TextureConfiguration &textureConfiguration);

  public:
    AssetManager();

    // TEXTURE

    void LoadTexture(const std::string &textureId, const std::string &filePath);
    Texture* GetTexture(const std::string &textureId);
    bool HasTexture(const std::string &textureId) const;

    // FONT
    void LoadFont(const std::string &fontId, const std::string &fontPath, int size);
    Font* GetFont(const std::string &fontId);
    bool HasFont(const std::string &fontId) const;

    // MUSIC
    void LoadMusic(const std::string &musicId, const std::string &musicPath);
    Mix_Music* GetMusic(const std::string &musicId);

    // SOUND
    void LoadSound(const std::string &soundId, const std::string &soundPath);
    Mix_Chunk* GetSound(const std::string &soundId);
    std::map<std::string, Mix_Chunk*> GetAllSounds();

    // AUDIO STREAM

    void LoadAudioStream(const std::string& audioStreamId, const std::string& audioStreamPath, float pitch = 1.0f, float gain = 1.0f, bool loops = false);
    AudioStream* GetAudioStream(const std::string& audioStreamId);

    // ALL ASSETS

    void LoadEngineAssets();

    void LoadProjectAssets();
};

#endif // ASSET_MANAGER_H
