#pragma once

#include "singleton.h"

#include <string>

#include <kuba_zip/zip.h>

struct Archive {
    void *fileBuffer = nullptr;
    size_t fileBufferSize = 0;
};

class ArchiveLoader : public Singleton<ArchiveLoader> {
  private:
    static ArchiveLoader *instance;
    struct zip_t *packageArchive = nullptr;

  public:
    ArchiveLoader(singleton) {}
    void ReadArchive(const std::string &filePath);
    Archive Load(const std::string &filePath);
    std::string LoadAsString(const std::string &filePath);
    bool HasArchiveInMemory() const;
    void PrintArchiveContents();
    void ClearArchive();
};
