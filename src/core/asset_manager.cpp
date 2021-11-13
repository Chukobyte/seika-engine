#include "asset_manager.h"

#include <iostream>
#include <cassert>

#include "global_dependencies.h"

AssetManager::AssetManager() {
    projectProperties = ProjectProperties::GetInstance();
    archiveLoader = ArchiveLoader::GetInstance();
    logger = Logger::GetInstance();
}

// TEXTURE
Texture *AssetManager::LoadTextureFromFile(const TextureConfiguration &textureConfiguration) {
    Texture *texture = new Texture(textureConfiguration.filePath.c_str(),
                                   textureConfiguration.wrapS,
                                   textureConfiguration.wrapT,
                                   textureConfiguration.filterMin,
                                   textureConfiguration.filterMax);
    assert(texture->IsValid());
    return texture;
}

Texture *AssetManager::LoadTextureFromMemory(const TextureConfiguration &textureConfiguration) {
    Archive archive = archiveLoader->Load(textureConfiguration.filePath);
    Texture *texture = new Texture(archive.fileBuffer,
                                   archive.fileBufferSize,
                                   textureConfiguration.wrapS,
                                   textureConfiguration.wrapT,
                                   textureConfiguration.filterMin,
                                   textureConfiguration.filterMax);
    assert(texture->IsValid());
    return texture;
}

void AssetManager::LoadTexture(const TextureConfiguration &textureConfiguration) {
    logger->Debug("Load texture file path = " + textureConfiguration.filePath);
    Texture *texture = nullptr;
    if (projectProperties->IsAssetsInMemory()) {
        texture = LoadTextureFromMemory(textureConfiguration);
    } else {
        texture = LoadTextureFromFile(textureConfiguration);
    }
    textures.emplace(textureConfiguration.filePath, texture);
}

// TODO: figure out if texture id is needed
void AssetManager::LoadTexture(const std::string &textureId, const std::string &filePath) {
    LoadTexture(TextureConfiguration{.filePath = filePath});
}

Texture* AssetManager::GetTexture(const std::string &textureId) {
    assert(textures.count(textureId) > 0 && "Texture Id not found!");
    return textures[textureId];
}

bool AssetManager::HasTexture(const std::string &textureId) const {
    return textures.count(textureId) > 0;
}

// FONT
void AssetManager::LoadFont(const std::string &fontId, const std::string &fontPath, int size) {
    static RenderContext *renderContext = GD::GetContainer()->renderContext;
    Font *font = new Font(fontId, renderContext->freeTypeLibrary, fontPath.c_str(), size);
    fonts.emplace(fontId, font);
}

Font* AssetManager::GetFont(const std::string &fontId) {
    assert(fonts.count(fontId) > 0 && "Font hasn't been loaded!");
    return fonts[fontId];
}

bool AssetManager::HasFont(const std::string &fontId) const {
    return fonts.count(fontId) > 0;
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
    LoadTexture(TextureConfiguration{.filePath = DEFAULT_COLLIDER_ASSET_ID});
    LoadFont(DEFAULT_FONT_ASSET_ID, DEFAULT_FONT_ASSET_PATH, DEFAULT_FONT_SIZE);
}

void AssetManager::LoadProjectAssets() {
    AssetConfigurations assetConfigurations = projectProperties->GetAssetConfigurations();

    for (TextureConfiguration textureConfiguration : assetConfigurations.textureConfigurations) {
        LoadTexture(textureConfiguration);
    }

    for (FontConfiguration fontConfiguration : assetConfigurations.fontConfigurations) {
        LoadFont(fontConfiguration.uid, fontConfiguration.filePath, fontConfiguration.size);
    }

    for (MusicConfiguration musicConfiguration : assetConfigurations.musicConfigurations) {
        LoadMusic(musicConfiguration.filePath, musicConfiguration.filePath);
    }

    for (SoundConfiguration soundConfiguration : assetConfigurations.soundConfigurations) {
        LoadSound(soundConfiguration.filePath, soundConfiguration.filePath);
    }
}
