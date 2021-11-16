#ifndef PROJECT_PROPERTIES_H
#define PROJECT_PROPERTIES_H

#include <string>
#include <vector>

#include "utils/json_file_helper.h"
#include "utils/logger.h"

#include "color.h"

struct TextureConfiguration {
    std::string filePath;
    std::string wrapS;
    std::string wrapT;
    std::string filterMin;
    std::string filterMax;
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

struct AssetConfigurations {
    std::vector<TextureConfiguration> textureConfigurations;
    std::vector<FontConfiguration> fontConfigurations;
    std::vector<MusicConfiguration> musicConfigurations;
    std::vector<SoundConfiguration> soundConfigurations;
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
    AssetConfigurations assetConfigurations;
    InputActionsConfigurations inputActionsConfigurations;

    ProjectProperties() = default;

    void LoadProjectAssets(nlohmann::json assetsJsonArray) {
        AssetConfigurations loadedAssetConfigurations;
        for (nlohmann::json assetJson : assetsJsonArray) {
            const std::string &assetType = assetJson["type"].get<std::string>();
            const std::string &assetsFilePath = assetJson["file_path"].get<std::string>();
            if (assetType == "texture") {
                const std::string &assetWrapS = assetJson["wrap_s"].get<std::string>();
                const std::string &assetWrapT = assetJson["wrap_s"].get<std::string>();
                const std::string &assetFilterMin = assetJson["filter_min"].get<std::string>();
                const std::string &assetFilterMax = assetJson["filter_max"].get<std::string>();
                loadedAssetConfigurations.textureConfigurations.emplace_back(TextureConfiguration{
                    .filePath = assetsFilePath,
                    .wrapS = assetWrapS,
                    .wrapT = assetWrapT,
                    .filterMin = assetFilterMin,
                    .filterMax = assetFilterMax
                });
            } else if (assetType == "font") {
                const std::string &fontId = assetJson["uid"].get<std::string>();
                int fontSize = assetJson["size"].get<int>();
                loadedAssetConfigurations.fontConfigurations.emplace_back(FontConfiguration{
                    .filePath = assetsFilePath,
                    .uid = fontId,
                    .size = fontSize
                });
            } else if (assetType == "music") {
                loadedAssetConfigurations.musicConfigurations.emplace_back(MusicConfiguration{
                    .filePath = assetsFilePath
                });
            } else if (assetType == "sound") {
                loadedAssetConfigurations.soundConfigurations.emplace_back(SoundConfiguration{
                    .filePath = assetsFilePath
                });
            }
        }
        assetConfigurations = loadedAssetConfigurations;
    }

    void LoadProjectInputActions(nlohmann::json inputActionsJsonArray) {
        InputActionsConfigurations loadInputActionsConfigurations;
        for (nlohmann::json inputActionJson : inputActionsJsonArray) {
            const std::string &actionName = inputActionJson["name"].get<std::string>();
            std::vector<std::string> inputActionValues;
            nlohmann::json actionValuesArray = inputActionJson["values"].get<nlohmann::json>();
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
    Color backgroundDrawColor = Color(20.f / 255.0f, 20.f / 255.0f, 20.f / 255.0f);
    bool areColliderVisible = false;
    std::string initialScenePath;

    static ProjectProperties* GetInstance();

    unsigned int GetTargetFPS() {
        return targetFPS;
    }

    void SetTargetFPS(unsigned int fps) {
        targetFPS = fps;
    }

    double GetMillisecondsPerTick() {
        return millisecondsPerTick;
    }

    double GetMaxDeltaTime() {
        return maxDeltaTime;
    }

    double GetFixedPhysicsDeltaTime() {
        return fixedPhysicsDeltaTime;
    }

    AssetConfigurations GetAssetConfigurations() {
        return assetConfigurations;
    }

    InputActionsConfigurations GetInputActionsConfigurations() {
        return inputActionsConfigurations;
    }

    void LoadProjectConfigurations(const std::string projectFilePath) {
        Logger::GetInstance()->Debug("Loading project config from path " + projectFilePath);
        nlohmann::json projectConfigurationsJson = JsonFileHelper::LoadJsonFile(projectFilePath);

        gameTitle = projectConfigurationsJson["game_title"].get<std::string>();
        initialScenePath = projectConfigurationsJson["initial_scene"].get<std::string>();
        nlohmann::json baseResolutionJson = projectConfigurationsJson["base_resolution"].get<nlohmann::json>();
        windowWidth = baseResolutionJson["width"].get<int>();
        windowHeight = baseResolutionJson["height"].get<int>();
        areColliderVisible = projectConfigurationsJson["colliders_visible"].get<bool>();
        targetFPS = projectConfigurationsJson["target_fps"].get<unsigned int>();
        float backgroundRed = projectConfigurationsJson["background_color"]["red"].get<float>();
        float backgroundGreen = projectConfigurationsJson["background_color"]["green"].get<float>();
        float backgroundBlue = projectConfigurationsJson["background_color"]["blue"].get<float>();
        backgroundDrawColor = Color(backgroundRed, backgroundGreen, backgroundBlue);

        nlohmann::json assetsJsonArray = projectConfigurationsJson["assets"].get<nlohmann::json>();
        LoadProjectAssets(assetsJsonArray);

        nlohmann::json inputActionsJsonArray = projectConfigurationsJson["input_actions"].get<nlohmann::json>();
        LoadProjectInputActions(inputActionsJsonArray);
    }
};

#endif //PROJECT_PROPERTIES_H
