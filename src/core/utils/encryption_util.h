#pragma once

#include <fstream>
#include <sys/stat.h>
#include "cassert"

enum class EncryptionCoding : int {
    ENCRYPT = 1,
    DECRYPT = -1,
};

namespace EncryptionUtil {
int getCypherKeyValue(const std::string& key, const int& pos);
void cypherFile (std::fstream& file, const std::string& key, EncryptionCoding coding);
bool DoesFileExist(const std::string &name);
double GetFileSize(const std::string &filePath);
void EncryptFile(const std::string &filePath, const std::string &key);
void DecryptFile(const std::string &filePath, const std::string &key);
}
