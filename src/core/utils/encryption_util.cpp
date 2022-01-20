#include "encryption_util.h"

namespace EncryptionUtil {
int getCypherKeyValue(const std::string& key, const int& pos) {
    return key[pos % key.length()];
}
void cypherFile (std::fstream& file, const std::string& key, EncryptionCoding coding) {
    char c;
    for (int i=0; file.get(c); i++) {
        c += (int) coding * getCypherKeyValue(key, i);
        file.seekg(i, file.beg);
        file.put(c);
    }
}
bool DoesFileExist(const std::string &name) {
    struct stat buffer;
    return(stat(name.c_str(), &buffer) == 0);
}

double GetFileSize(const std::string &filePath) {
    std::ifstream file(filePath.c_str(), std::ios::ate);

    double fileSize = file.tellg();
    file.close();

    return fileSize;
}

void EncryptFile(const std::string &filePath, const std::string &key) {
    assert(DoesFileExist(filePath) && "File doesn't exist!");
    std::fstream fileStream(filePath);
    cypherFile(fileStream, key, EncryptionCoding::ENCRYPT);
}

void DecryptFile(const std::string &filePath, const std::string &key) {
    assert(DoesFileExist(filePath) && "File doesn't exist!");
    std::fstream fileStream(filePath, std::ios::in | std::ios::out);
    cypherFile(fileStream, key, EncryptionCoding::DECRYPT);
}
}
