#ifndef TEXTURE_2D_H
#define TEXTURE_2D_H

#include <glad/glad.h>

#include "../utils/logger.h"

class Texture {
  private:
    static Logger *logger;
    std::string fileName;

    GLuint ID = 0;
    unsigned char* data = nullptr;
    int width = 0;
    int height = 0;
    int nrChannels = 0;
    // format
    unsigned int internalFormat = GL_RGBA;
    unsigned int imageFormat = GL_RGBA;
    // configuration
    unsigned int wrapS = GL_CLAMP_TO_BORDER;
    unsigned int wrapT = GL_CLAMP_TO_BORDER;
    unsigned int filterMin = GL_NEAREST;
    unsigned int filterMax = GL_NEAREST;

    void Initialize(const char* fileName);

    void Initialize(void *buffer, size_t bufferSize);

    void Generate();
  protected:
    Texture() {}
  public:
    Texture(const char* fileName);

    Texture(const char* fileName, unsigned int wrapS, unsigned int wrapT, unsigned int filterMax, unsigned int filterMin);

    Texture(void *buffer, size_t bufferSize);

    ~Texture();

    void Bind() const;

    std::string GetFilePath() const;

    int GetWidth() const;

    int GetHeight() const;

    unsigned int GetImageFormat() const;

    unsigned char* GetData() const;

    bool IsValid() const;
};


#endif //TEXTURE_2D_H
