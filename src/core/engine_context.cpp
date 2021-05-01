#include "engine_context.h"
#include "utils/json_file_helper.h"

void EngineContext::SetRunning(bool value) {
    running = value;
}
bool EngineContext::IsRunning() const {
    return running;
}

std::string EngineContext::GetEngineVersion() {
    if (engineVersion.empty()) {
        const std::string &versionFilePath = "version.json";
        nlohmann::json versionJson = JsonFileHelper::LoadJsonFile(versionFilePath);
        engineVersion = versionJson["version"].get<std::string>();
    }
    return engineVersion;
}
