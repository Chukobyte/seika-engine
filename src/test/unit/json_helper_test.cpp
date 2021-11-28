#include <catch.hpp>
#include "../../core/utils/json_helper.h"

TEST_CASE("Json Helper Tests", "[json_helper]") {
    SECTION("Has Key") {
        nlohmann::json testJson;
        testJson["is_testing"] = true;

        REQUIRE(JsonHelper::HasKey(testJson, "is_testing"));

        REQUIRE(!JsonHelper::HasKey(testJson, "non_existant"));
    }

    SECTION("Get From Key") {
        nlohmann::json testJson;
        testJson["level"] = 1;

        int loadedLevel = JsonHelper::Get<int>(testJson, "level");

        REQUIRE(loadedLevel == 1);

        REQUIRE(JsonHelper::GetDefault<int>(testJson, "power", 10) == 10);
    }
}
