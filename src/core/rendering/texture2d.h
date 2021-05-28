#ifndef TEXTURE_2D_H
#define TEXTURE_2D_H

#include <glad/glad.h>

#include "../utils/logger.h"

class Texture2D {
  private:
    static Logger *logger;
    std::string fileName;

    void Initialize(const char* fileName);

    void Initialize(void *buffer, size_t bufferSize);

    void Generate();
  protected:
    Texture2D() {}
  public:
    GLuint ID = 0;
    unsigned char* data = nullptr;
    int width = 0;
    int height = 0;
    int nrChannels;
    // format
    unsigned int internalFormat = GL_RGBA;
    unsigned int imageFormat = GL_RGBA;
    // configuration
    unsigned int wrapS = GL_CLAMP_TO_BORDER;
    unsigned int wrapT = GL_CLAMP_TO_BORDER;
    unsigned int filterMin = GL_NEAREST;
    unsigned int filterMax = GL_NEAREST;

    Texture2D(const char* fileName);

    Texture2D(const char* fileName, unsigned int wrapS, unsigned int wrapT, unsigned int filterMax, unsigned int filterMin);

    Texture2D(void *buffer, size_t bufferSize);

    ~Texture2D();

    void Bind() const;

    std::string GetFilePath() const;

    bool IsValid() const;
};


#endif //TEXTURE_2D_H
