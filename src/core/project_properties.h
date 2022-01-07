#ifndef PROJECT_PROPERTIES_H
#define PROJECT_PROPERTIES_H

#include <string>
#include <vector>

#include "utils/json_helper.h"
#include "utils/json_file_helper.h"
#include "utils/logger.h"
#include "utils/archive_loader.h"

#include "color.h"

struct TextureConfiguration {
    std::string filePath;
    std::string wrapS = "clamp_to_border";
    std::string wrapT = "clamp_to_border";
    std::string filterMin = "nearest";
    std::string filterMax = "nearest";
};

struct FontConfiguration {
    std::string filePath;
    std::string uid;
    int size;
};

struct MusicConfiguration {
    std::string filePath;
};

struct SoundConfiguration {
    std::string filePath;
};

struct AudioStreamConfiguration {
    std::string filePath;
    std::string uid;
    float pitch;
    float gain;
    bool loops;
};

struct AssetConfigurations {
    std::vector<TextureConfiguration> textureConfigurations = {};
    std::vector<FontConfiguration> fontConfigurations = {};
    std::vector<MusicConfiguration> musicConfigurations = {};
    std::vector<SoundConfiguration> soundConfigurations = {};
    std::vector<AudioStreamConfiguration> audioStreamConfigurations = {};
};

struct InputConfiguration {
    std::string name;
    std::vector<std::string> values;
};

struct InputActionsConfigurations {
    std::vector<InputConfiguration> configurations;
};

class ProjectProperties {
  private:
    static ProjectProperties *instance;
    unsigned int targetFPS = 66;
    double millisecondsPerTick = 1000.0f;
    double maxDeltaTime = 0.5f;
    double fixedPhysicsDeltaTime = 0.01f;
    bool assetsInMemory = true;
    bool pixelSnap = false;
    AssetConfigurations assetConfigurations;
    InputActionsConfigurations inputActionsConfigurations;

    ArchiveLoader *archiveLoader = nullptr;

    ProjectProperties() {
        archiveLoader = ArchiveLoader::GetInstance();
    };

    void ConfigureConfigurationJson(const nlohmann::json &projectConfigurationsJson) {
        gameTitle = JsonHelper::Get<std::string>(projectConfigurationsJson, "game_title");
        initialScenePath = JsonHelper::Get<std::string>(projectConfigurationsJson, "initial_scene");
        nlohmann::json baseResolutionJson = JsonHelper::Get<nlohmann::json>(projectConfigurationsJson, "base_resolution");
        windowWidth = JsonHelper::Get<int>(baseResolutionJson, "width");
        windowHeight = JsonHelper::Get<int>(baseResolutionJson, "height");
        areColliderVisible = JsonHelper::Get<bool>(projectConfigurationsJson, "colliders_visible");
        pixelSnap = JsonHelper::GetDefault<bool>(projectConfigurationsJson, "pixel_snap", false);
        targetFPS = JsonHelper::Get<unsigned int>(projectConfigurationsJson, "target_fps");
        nlohmann::json backgroundColorJson = JsonHelper::Get<nlohmann::json>(projectConfigurationsJson, "background_color");
        const float backgroundRed = JsonHelper::Get<float>(backgroundColorJson, "red");
        const float backgroundGreen = JsonHelper::Get<float>(backgroundColorJson, "green");
        const float backgroundBlue = JsonHelper::Get<float>(backgroundColorJson, "blue");
        backgroundDrawColor = Color(backgroundRed, backgroundGreen, backgroundBlue);

        nlohmann::json assetsJsonArray = JsonHelper::Get<nlohmann::json>(projectConfigurationsJson, "assets");
        LoadProjectAssets(assetsJsonArray);

        nlohmann::json inputActionsJsonArray = JsonHelper::Get<nlohmann::json>(projectConfigurationsJson, "input_actions");
        LoadProjectInputActions(inputActionsJsonArray);
    }

    void LoadProjectAssets(nlohmann::json assetsJsonArray) {
        AssetConfigurations loadedAssetConfigurations;
        for (nlohmann::json assetJson : assetsJsonArray) {
            const std::string &assetType = JsonHelper::Get<std::string>(assetJson, "type");
            const std::string &assetsFilePath = JsonHelper::Get<std::string>(assetJson, "file_path");
            if (assetType == "texture") {
                const std::string &assetWrapS = JsonHelper::Get<std::string>(assetJson, "wrap_s");
                const std::string &assetWrapT = JsonHelper::Get<std::string>(assetJson, "wrap_t");
                const std::string &assetFilterMin = JsonHelper::Get<std::string>(assetJson, "filter_min");
                const std::string &assetFilterMax = JsonHelper::Get<std::string>(assetJson, "filter_max");
                loadedAssetConfigurations.textureConfigurations.emplace_back(TextureConfiguration{
                    assetsFilePath,
                    assetWrapS,
                    assetWrapT,
                    assetFilterMin,
                    assetFilterMax
                });
            } else if (assetType == "font") {
                const std::string &fontId = JsonHelper::Get<std::string>(assetJson, "uid");
                int fontSize = JsonHelper::Get<int>(assetJson, "size");
                loadedAssetConfigurations.fontConfigurations.emplace_back(FontConfiguration{
                    assetsFilePath,
                    fontId,
                    fontSize
                });
            } else if (assetType == "music") {
                loadedAssetConfigurations.musicConfigurations.emplace_back(MusicConfiguration{
                    assetsFilePath
                });
            } else if (assetType == "sound") {
                loadedAssetConfigurations.soundConfigurations.emplace_back(SoundConfiguration{
                    assetsFilePath
                });
            } else if (assetType == "audio_stream") {
                const std::string &audioStreamId = JsonHelper::Get<std::string>(assetJson, "uid");
                const float audioStreamPitch = JsonHelper::Get<float>(assetJson, "pitch");
                const float audioStreamGain = JsonHelper::Get<float>(assetJson, "gain");
                const bool audioStreamLoops = JsonHelper::Get<bool>(assetJson, "loops");
                loadedAssetConfigurations.audioStreamConfigurations.emplace_back(AudioStreamConfiguration{
                    assetsFilePath,
                    audioStreamId,
                    audioStreamPitch,
                    audioStreamGain,
                    audioStreamLoops
                });
            }
        }
        assetConfigurations = loadedAssetConfigurations;
    }

    void LoadProjectInputActions(nlohmann::json inputActionsJsonArray) {
        InputActionsConfigurations loadInputActionsConfigurations;
        for (nlohmann::json inputActionJson : inputActionsJsonArray) {
            const std::string &actionName = JsonHelper::Get<std::string>(inputActionJson, "name");
            std::vector<std::string> inputActionValues;
            nlohmann::json actionValuesArray = JsonHelper::Get<nlohmann::json>(inputActionJson, "values");
            for (const auto &value : actionValuesArray) {
                inputActionValues.emplace_back(value);
            }
            InputConfiguration inputConfiguration{
                .name = actionName,
                .values = inputActionValues
            };
            loadInputActionsConfigurations.configurations.emplace_back(inputConfiguration);
        }
        inputActionsConfigurations = loadInputActionsConfigurations;
    }
  public:
    std::string gameTitle = "Seika Engine";
    int windowWidth = 800;
    int windowHeight = 600;
    Color backgroundDrawColor = Color::NormalizedColor(20, 20, 20);
    bool areColliderVisible = false;
    std::string initialScenePath;
    std::string assetArchivePath;

    static ProjectProperties* GetInstance();

    unsigned int GetTargetFPS() const {
        return targetFPS;
    }

    void SetTargetFPS(unsigned int fps) {
        targetFPS = fps;
    }

    double GetMillisecondsPerTick() const {
        return millisecondsPerTick;
    }

    double GetMaxDeltaTime() const {
        return maxDeltaTime;
    }

    double GetFixedPhysicsDeltaTime() const {
        return fixedPhysicsDeltaTime;
    }

    bool IsAssetsInMemory() const {
        return assetsInMemory;
    }

    bool IsPixelSnapEnabled() const {
        return pixelSnap;
    }

    AssetConfigurations GetAssetConfigurations() {
        return assetConfigurations;
    }

    InputActionsConfigurations GetInputActionsConfigurations() {
        return inputActionsConfigurations;
    }

    void LoadProjectConfigurationsFromFile(const std::string projectFilePath) {
        Logger::GetInstance()->Debug("Loading project config from file path " + projectFilePath);
        assetsInMemory = false;
        nlohmann::json projectConfigurationsJson = JsonFileHelper::LoadJsonFile(projectFilePath);
        ConfigureConfigurationJson(projectConfigurationsJson);
    }

    void LoadProjectConfigurationsFromMemory(const std::string projectFilePath) {
        Logger::GetInstance()->Debug("Loading project config from memory path " + projectFilePath);
        assetsInMemory = true;
        const std::string &projectFileJsonString = archiveLoader->LoadAsString(projectFilePath);
        nlohmann::json projectConfigurationsJson = JsonFileHelper::ConvertStringToJson(projectFileJsonString);
        ConfigureConfigurationJson(projectConfigurationsJson);
    }
};

#endif //PROJECT_PROPERTIES_H
