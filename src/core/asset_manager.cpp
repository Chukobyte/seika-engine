#include "asset_manager.h"

#include <iostream>
#include <cassert>

#include "global_dependencies.h"
#include "project_properties.h"

AssetManager::AssetManager() {
    logger = Logger::GetInstance();
}

// TEXTURE
void AssetManager::LoadTexture(const std::string &textureId, const std::string &filePath) {
    Texture *texture = new Texture(filePath.c_str());
    assert(texture->IsValid());
    textures.emplace(textureId, texture);
}

Texture* AssetManager::GetTexture(const std::string &textureId) {
    assert(textures.count(textureId) > 0 && "Texture Id not found!");
    return textures[textureId];
}

// FONT
void AssetManager::LoadFont(const std::string &fontId, const std::string &fontPath, int size) {
    static RenderContext *renderContext = GD::GetContainer()->renderContext;
    Font *font = new Font(renderContext->freeTypeLibrary, fontPath.c_str(), size);
    fonts.emplace(fontId, font);
}

Font* AssetManager::GetFont(const std::string &fontId) {
    assert(fonts.count(fontId) > 0 && "Font hasn't been loaded!");
    return fonts[fontId];
}

// MUSIC
void AssetManager::LoadMusic(const std::string &musicId, const std::string &musicPath) {
    Mix_Music *newMusic = Mix_LoadMUS(musicPath.c_str());
    if (!newMusic) {
        logger->Error("Error loading music at '" + musicPath + "'\n" + Mix_GetError());
    } else {
        music.emplace(musicId, newMusic);
    }
}

Mix_Music* AssetManager::GetMusic(const std::string &musicId) {
    assert(music.count(musicId) > 0 && "Doesn't have music!");
    return music[musicId];
}

// SOUND
void AssetManager::LoadSound(const std::string &soundId, const std::string &soundPath) {
    Mix_Chunk *newSound = Mix_LoadWAV(soundPath.c_str());
    if (!newSound) {
        logger->Error("Error loading sound at '" + soundPath + "'\n" + Mix_GetError());
    } else {
        sounds.emplace(soundId, newSound);
    }
}

Mix_Chunk* AssetManager::GetSound(const std::string &soundId) {
    assert(sounds.count(soundId) > 0 && "Doesn't have sound!");
    return sounds[soundId];
}

std::map<std::string, Mix_Chunk*> AssetManager::GetAllSounds() {
    return sounds;
}

void AssetManager::LoadEngineAssets() {
    LoadTexture(DEFAULT_COLLIDER_ASSET_ID, DEFAULT_COLLIDER_ASSET_ID);
}

void AssetManager::LoadProjectAssets() {
    ProjectProperties *projectProperties = ProjectProperties::GetInstance();
    AssetConfigurations assetConfigurations = projectProperties->GetAssetConfigurations();

    for (TextureConfiguration textureConfiguration : assetConfigurations.textureConfigurations) {
        LoadTexture(textureConfiguration.filePath, textureConfiguration.filePath);
    }

    for (FontConfiguration fontConfiguration : assetConfigurations.fontConfigurations) {
        LoadFont(fontConfiguration.filePath, fontConfiguration.filePath, fontConfiguration.size);
    }

    for (MusicConfiguration musicConfiguration : assetConfigurations.musicConfigurations) {
        LoadMusic(musicConfiguration.filePath, musicConfiguration.filePath);
    }

    for (SoundConfiguration soundConfiguration : assetConfigurations.soundConfigurations) {
        LoadSound(soundConfiguration.filePath, soundConfiguration.filePath);
    }
}
