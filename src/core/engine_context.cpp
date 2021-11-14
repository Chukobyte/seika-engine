#include "engine_context.h"
#include "utils/json_file_helper.h"
#include "utils/logger.h"
#include "utils/archive_loader.h"

void EngineContext::SetRunning(bool value) {
    running = value;
}
bool EngineContext::IsRunning() const {
    return running;
}

std::string EngineContext::GetEngineVersion(const bool loadFromMemory) {
    if (engineVersion.empty()) {
        const std::string &versionFilePath = "_version.json";
        Logger::GetInstance()->Debug("version file path = " + versionFilePath);
        nlohmann::json versionJson;
        if (loadFromMemory) {
            const std::string &versionJsonString = ArchiveLoader::GetInstance()->LoadAsString(versionFilePath);
            versionJson = JsonFileHelper::ConvertStringToJson(versionJsonString);
        } else {
            versionJson = JsonFileHelper::LoadJsonFile(versionFilePath);
        }
        engineVersion = versionJson["version"].get<std::string>();
    }
    return engineVersion;
}

void EngineContext::StartFPSCounter() {
    fpsCounter.Start();
}

void EngineContext::UpdateFPSCounter() {
    fpsCounter.Update();
}

long EngineContext::GetFPS() const {
    return fpsCounter.averageFPS;
}
