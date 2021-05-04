#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include <map>
#include <string>

#include <SDL2/SDL_mixer.h>

#include "rendering/texture2d.h"
#include "rendering/font.h"

class AssetManager {
  private:
    std::map<std::string, Texture2D*> textures;
    std::map<std::string, Font*> fonts;
    std::map<std::string, Mix_Music*> music;
    std::map<std::string, Mix_Chunk*> sounds;
    Logger *logger = nullptr;

  public:
    AssetManager();

    // TEXTURE
    void LoadTexture(const std::string &textureId, const std::string &filePath);

    Texture2D* GetTexture(const std::string &textureId);

    // FONT
    void LoadFont(const std::string &fontId, const std::string &fontPath, int size);

    Font* GetFont(const std::string &fontId);
//
    // MUSIC
    void LoadMusic(const std::string &musicId, const std::string &musicPath);

    Mix_Music* GetMusic(const std::string &musicId);

    // SOUND
    void LoadSound(const std::string &soundId, const std::string &soundPath);

    Mix_Chunk* GetSound(const std::string &soundId);

    std::map<std::string, Mix_Chunk*> GetAllSounds();

    void LoadProjectAssets();
};

#endif // ASSET_MANAGER_H
