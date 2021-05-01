#include <catch.hpp>
#include "../../core/utils/json_file_helper.h"

TEST_CASE("Json File Helper Tests", "[json_file_helper]") {
    SECTION("Load Json File") {
        nlohmann::json fileJson = JsonFileHelper::LoadJsonFile("./src/test/resources/test.json");
        const std::string &messageFromFile = fileJson["message"].get<std::string>();

        REQUIRE(messageFromFile == "hello");
    }
}
