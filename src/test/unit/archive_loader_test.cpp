#include <catch.hpp>
#include "../../core/utils/archive_loader.h"

TEST_CASE("Archive Loader Tests", "[archive_loader]") {
    ArchiveLoader *archiveLoader = ArchiveLoader::GetInstance();
    archiveLoader->ReadArchive("src/test/resources/test_archive.zip");

    SECTION("Is Zip in memory") {
        REQUIRE(archiveLoader->HasArchiveInMemory());
    }

    SECTION("Load archive file") {
        Archive archive = archiveLoader->Load("test.txt");
        REQUIRE(archive.fileBuffer != nullptr);
        REQUIRE(archive.fileBufferSize > 0);
    }

    SECTION("Load archive file as a string") {
        const std::string &archiveString = archiveLoader->LoadAsString("test.txt");
        REQUIRE(archiveString == "Hello World!\r\n");
    }

    archiveLoader->ClearArchive();
}
