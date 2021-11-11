#ifndef FILE_HELPER_H
#define FILE_HELPER_H

#include <experimental/filesystem>
#include "SDL2/SDL.h"

#include "encryption_util.h"
#include "json_file_helper.h"

class FileHelper {
  private:
    static std::string GetSaveDataPath(const std::string &filePath, const std::string &applicationName) {
        return GetUserSavePath(applicationName) + filePath;
    }
  public:
    static bool DoesFileExist(const std::string &name) {
        return EncryptionUtil::DoesFileExist(name);
    }

    static void ChangeDirectory(const std::string &newDirectory) {
        chdir(newDirectory.c_str());
    }

    static std::string GetUserSavePath(const std::string &applicationName) {
        char *appDataPath = SDL_GetPrefPath("seika_engine", applicationName.c_str());
        return std::string(appDataPath);
    }

    static bool DoesUserSaveFileExists(const std::string &filePath, const std::string &applicationName) {
        const std::string& savePath = GetSaveDataPath(filePath, applicationName);
        return DoesFileExist(savePath);
    }

    static void SaveGameData(const std::string &filePath, const std::string &jsonDataString, const std::string &applicationName) {
        nlohmann::json jsonData = JsonFileHelper::ConvertStringToJson(jsonDataString);
        const std::string& savePath = GetSaveDataPath(filePath, applicationName);
        JsonFileHelper::SaveJsonFile(savePath, jsonData);
    }

    static void SaveGameDataEncrypted(const std::string &filePath, const std::string &jsonDataString, const std::string &applicationName, const std::string &encryptionKey) {
        SaveGameData(filePath, jsonDataString, applicationName);
        const std::string& savePath = GetSaveDataPath(filePath, applicationName);
        EncryptionUtil::EncryptFile(savePath, encryptionKey);
    }

    static std::string LoadGameData(const std::string &filePath, const std::string &applicationName) {
        const std::string &savePath = GetSaveDataPath(filePath, applicationName);
        nlohmann::json jsonData = JsonFileHelper::LoadJsonFile(savePath);
        return jsonData.dump();
    }

    static std::string LoadGameDataEncrypted(const std::string &filePath, const std::string &applicationName, const std::string &encryptionKey) {
        const std::string& savePath = GetSaveDataPath(filePath, applicationName);
        EncryptionUtil::DecryptFile(savePath, encryptionKey);
        const std::string &gameData = LoadGameData(filePath, applicationName);
        EncryptionUtil::EncryptFile(savePath, encryptionKey);
        return gameData;
    }

    static bool DeleteGameData(const std::string &filePath, const std::string &applicationName) {
        const std::string& savePath = GetSaveDataPath(filePath, applicationName);
        if (remove(savePath.c_str()) == 0) {
            return true;
        }
        return false;
    }

    static std::string GetFileNameFromPath(const std::string &filePath) {
        const size_t &fileNamePosition = filePath.find_last_of("/");
        if (fileNamePosition != std::string::npos) {
            return filePath.substr(fileNamePosition + 1);
        }
        return filePath;
    }

    static std::string GetFileNameFromPathWithoutExtension(const std::string &filePath) {
        std::string fileName = GetFileNameFromPath(filePath);
        const size_t &fileNamePosition = fileName.find_last_of(".");
        if (fileNamePosition != std::string::npos) {
            const std::string fileExtension = fileName.substr(fileNamePosition + 1);
            fileName.resize(fileName.size() - (fileExtension.size() + 1));
            return fileName;
        }
        return fileName;
    }
};

#endif //FILE_HELPER_H
