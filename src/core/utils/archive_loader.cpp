#include "archive_loader.h"

#include <iostream>
#include <cassert>

#include "file_helper.h"

ArchiveLoader *ArchiveLoader::instance = nullptr;

ArchiveLoader *ArchiveLoader::GetInstance() {
    if (!instance) {
        instance = new ArchiveLoader();
    }
    return instance;
}

void ArchiveLoader::ReadArchive(const std::string &filePath) {
    assert(FileHelper::DoesFileExist(filePath) && "Archive file doesn't exist!");
    ClearArchive();
    packageArchive = zip_open(filePath.c_str(), 0, 'r');
}

Archive ArchiveLoader::Load(const std::string &filePath) {
    assert(packageArchive != nullptr && "Cannot load archive, null in memory!");
    void *fileBuffer = nullptr;
    size_t fileBufferSize;
    zip_entry_open(packageArchive, filePath.c_str());
    {
        zip_entry_read(packageArchive, &fileBuffer, &fileBufferSize);
    }
    return Archive{
        .fileBuffer = fileBuffer,
        .fileBufferSize = fileBufferSize
    };
}

std::string ArchiveLoader::LoadString(const std::string &filePath) {
    Archive archive = Load(filePath);
    char *bufferOutput = (char*) archive.fileBuffer;
    const std::string &bufferText = std::string(bufferOutput, archive.fileBufferSize);
    return bufferText;
}

bool ArchiveLoader::HasArchiveInMemory() const {
    return packageArchive != nullptr;
}

void ArchiveLoader::ClearArchive() {
    if (packageArchive) {
        delete packageArchive;
    }
}

void ArchiveLoader::PrintArchiveContents() {
    assert(packageArchive != nullptr && "Cannot print archive contents, null in memory!");
    const int archiveEntries = zip_total_entries(packageArchive);
    for(int i = 0; i < archiveEntries; i++) {
        zip_entry_openbyindex(packageArchive, i);
        {
            const char *name = zip_entry_name(packageArchive);
            int isDir = zip_entry_isdir(packageArchive);
            unsigned long long size = zip_entry_size(packageArchive);
            unsigned int crc32 = zip_entry_crc32(packageArchive);
            std::cerr << "name: " << name << std::endl;
        }
        zip_entry_close(packageArchive);
    }
}
