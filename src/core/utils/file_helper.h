#ifndef FILE_HELPER_H
#define FILE_HELPER_H

#include <sys/stat.h>

class FileHelper {
  public:
    static bool DoesFileExist(const std::string &name) {
        struct stat buffer;
        return(stat(name.c_str(), &buffer) == 0);
    }

    static void ChangeDirectory(const std::string &newDirectory) {
        chdir(newDirectory.c_str());
    }
};

#endif //FILE_HELPER_H
