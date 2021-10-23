#ifndef JSON_FILE_HELPER_H
#define JSON_FILE_HELPER_H

#include <fstream>
#include <json/json.hpp>
#include <sstream>

class JsonFileHelper {
  public:
    static nlohmann::json LoadJsonFile(const std::string &filePath) {
        std::ifstream i(filePath);
        nlohmann::json json;
        i >> json;
        return json;
    }

    static void SaveJsonFile(const std::string &filePath, nlohmann::json outputJson) {
        std::ofstream myFile(filePath);
        myFile << outputJson;
        myFile.close();
    }

    static bool IsJsonValid(const std::string &jsonText) {
        return nlohmann::json::accept(jsonText);
    }

    static nlohmann::json ConvertStringToJson(const std::string &jsonString) {
        std::stringstream ss;
        ss << jsonString;
        nlohmann::json outputJson;
        outputJson << ss;
        return outputJson;
    }
};

#endif //JSON_FILE_HELPER_H
