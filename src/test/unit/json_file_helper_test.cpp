#include <catch.hpp>
#include "../../core/utils/json_file_helper.h"

TEST_CASE("Json File Helper Tests", "[json_file_helper]") {
    SECTION("Load Json File") {
        nlohmann::json fileJson = JsonFileHelper::LoadJsonFile("./src/test/resources/test.json");
        const std::string &messageFromFile = fileJson["message"].get<std::string>();

        REQUIRE(messageFromFile == "hello");
    }

    SECTION("Is JSON String Valid") {
        const std::string &validJsonString = "{\"test\": true}";

        REQUIRE(JsonFileHelper::IsJsonValid(validJsonString));

        const std::string &invalidJsonString = "{okays";

        REQUIRE(!JsonFileHelper::IsJsonValid(invalidJsonString));
    }
}
