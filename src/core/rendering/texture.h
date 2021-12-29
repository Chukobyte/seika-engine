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
    unsigned int filterMag = GL_NEAREST;

    void Initialize(const char* fileName);
    void Initialize(void *buffer, size_t bufferSize);
    void Generate();
    unsigned int GetWrapFromString(const std::string &wrap) const;
    unsigned int GetFilterFromString(const std::string &filter) const;
  protected:
    Texture() = default;
  public:
    Texture(const char* fileName);
    Texture(const char* fileName, unsigned int wrapS, unsigned int wrapT, unsigned int filterMin, unsigned int filterMag);
    Texture(const char* fileName, const std::string &wrapS, const std::string &wrapT, const std::string &filterMin, const std::string &filterMag);
    Texture(void *buffer, size_t bufferSize);
    Texture(void *buffer, size_t bufferSize, unsigned int wrapS, unsigned int wrapT, unsigned int filterMin, unsigned int filterMag);
    Texture(void *buffer, size_t bufferSize, const std::string &wrapS, const std::string &wrapT, const std::string &filterMin, const std::string &filterMag);
    Texture(unsigned int width, unsigned int height, unsigned int colorValue = 255); // colorValue default to white
    ~Texture();
    void Bind() const;
    std::string GetFilePath() const;
    int GetWidth() const;
    int GetHeight() const;
    unsigned int GetImageFormat() const;
    unsigned char* GetData() const;
    std::string GetWrapSString() const;
    std::string GetWrapTString() const;
    std::string GetFilterMinString() const;
    std::string GetFilterMagString() const;
    bool IsValid() const;
};

#endif //TEXTURE_2D_H
