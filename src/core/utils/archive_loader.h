#ifndef ARCHIVE_LOADER_H
#define ARCHIVE_LOADER_H

#include <string>

#include <kuba_zip/zip.h>

struct Archive {
    void *fileBuffer = nullptr;
    size_t fileBufferSize = 0;
};

class ArchiveLoader {
  private:
    static ArchiveLoader *instance;
    struct zip_t *packageArchive = nullptr;

    ArchiveLoader() = default;
  public:
    static ArchiveLoader* GetInstance();

    void ReadArchive(const std::string &filePath);

    Archive Load(const std::string &filePath);

    std::string LoadAsString(const std::string &filePath);

    bool HasArchiveInMemory() const;

    void PrintArchiveContents();

    void ClearArchive();
};


#endif //ARCHIVE_LOADER_H
