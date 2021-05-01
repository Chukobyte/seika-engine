#ifndef TEXTURE_2D_H
#define TEXTURE_2D_H

#include <glad/glad.h>

#include "../utils/logger.h"

class Texture2D {
  private:
    void Generate();
    static Logger *logger;
    std::string fileName;
  protected:
    Texture() {}
  public:
    GLuint ID = 0;
    unsigned char* data = nullptr;
    int width;
    int height;
    int nrChannels;
    // format
    unsigned int internalFormat;
    unsigned int imageFormat;
    // configuration
    unsigned int wrapS;
    unsigned int wrapT;
    unsigned int filterMin;
    unsigned int filterMax;

    Texture2D(const char* fileName);
    Texture2D(void *buffer, size_t bufferSize);
    ~Texture2D();
    void Bind() const;
    std::string GetFilePath() const;
    bool IsValid() const;
};


#endif //TEXTURE_2D_H
