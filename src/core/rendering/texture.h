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

    unsigned int GetWrapFromString(const std::string &wrap) const {
        if (wrap == "clamp_to_border") {
            return GL_CLAMP_TO_BORDER;
        } else if (wrap == "repeat") {
            return GL_REPEAT;
        }
        logger->Error("'" + wrap + "' is an invalid wrap value!");
        return wrapS;
    }

    unsigned int GetFilterFromString(const std::string &filter) const {
        if (filter == "nearest") {
            return GL_NEAREST;
        } else if (filter == "linear") {
            return GL_LINEAR;
        }
        logger->Error("'" + filter + "' is an invalid filter value!");
        return filterMin;
    }
  protected:
    Texture() {}
  public:
    Texture(const char* fileName);

    Texture(const char* fileName, unsigned int wrapS, unsigned int wrapT, unsigned int filterMin, unsigned int filterMax);

    Texture(const char* fileName, const std::string &wrapS, const std::string &wrapT, const std::string &filterMin, const std::string &filterMax);

    Texture(void *buffer, size_t bufferSize);

    Texture(void *buffer, size_t bufferSize, unsigned int wrapS, unsigned int wrapT, unsigned int filterMin, unsigned int filterMax);

    Texture(void *buffer, size_t bufferSize, const std::string &wrapS, const std::string &wrapT, const std::string &filterMin, const std::string &filterMax);

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

    std::string GetFilterMaxString() const;

    bool IsValid() const;
};


#endif //TEXTURE_2D_H
