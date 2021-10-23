#include <catch.hpp>
#include "../../core/utils/file_helper.h"

TEST_CASE("File Helper Tests", "[file_helper]") {
    const std::string &nonEncryptedfilePath = "non_encrypted_test.sav";
    const std::string &encryptedfilePath = "encrypted_test.sav";
    const std::string &jsonDataString = "{\"test\":true}";
    const std::string &applicationName = "seika_engine_test";
    const std::string &encryptionKey = "password";

    SECTION("Save Game Data") {
        FileHelper::SaveGameData(nonEncryptedfilePath, jsonDataString, applicationName);
        REQUIRE(FileHelper::DoesUserSaveFileExists(nonEncryptedfilePath, applicationName));
    }

    SECTION("Save Game Data Encrypted") {
        FileHelper::SaveGameDataEncrypted(encryptedfilePath, jsonDataString, applicationName, encryptionKey);
        REQUIRE(FileHelper::DoesUserSaveFileExists(encryptedfilePath, applicationName));
    }

    SECTION("Load Game Data") {
        const std::string jsonData = FileHelper::LoadGameData(nonEncryptedfilePath, applicationName);
        REQUIRE(jsonData == jsonDataString);
    }

    SECTION("Load Game Data Encrypted") {
        const std::string jsonData = FileHelper::LoadGameDataEncrypted(encryptedfilePath, applicationName, encryptionKey);
        REQUIRE(jsonData == jsonDataString);
    }

    SECTION("Delete Game Data") {
        FileHelper::DeleteGameData(nonEncryptedfilePath, applicationName);
        REQUIRE(!FileHelper::DoesUserSaveFileExists(nonEncryptedfilePath, applicationName));

        FileHelper::DeleteGameData(encryptedfilePath, applicationName);
        REQUIRE(!FileHelper::DoesUserSaveFileExists(encryptedfilePath, applicationName));
    }
}
