#ifndef JSON_FILE_HELPER_H
#define JSON_FILE_HELPER_H

#include <fstream>
#include <json/json.hpp>

class JsonFileHelper {
  public:
    static nlohmann::json LoadJsonFile(const std::string &filePath) {
        std::ifstream i(filePath);
        nlohmann::json json;
        i >> json;
        return json;
    }

    static bool IsJsonValid(const std::string &jsonText) {
        return nlohmann::json::accept(jsonText);
    }
};

#endif //JSON_FILE_HELPER_H
