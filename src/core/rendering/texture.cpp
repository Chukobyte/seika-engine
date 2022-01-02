#include "texture.h"

#include <stb_image/stb_image.h>

Logger *Texture::logger = Logger::GetInstance();

Texture::Texture(const char* fileName) {
    Initialize(fileName);
}

Texture::Texture(const char* fileName, unsigned int wrapS, unsigned int wrapT, unsigned int filterMin, unsigned int filterMag) :
    wrapS(wrapS), wrapT(wrapT), filterMin(filterMin), filterMag(filterMag) {
    Initialize(fileName);
}

Texture::Texture(const char* fileName, const std::string &wrapS, const std::string &wrapT, const std::string &filterMin, const std::string &filterMag) :
    wrapS(GetWrapFromString(wrapS)), wrapT(GetWrapFromString(wrapT)), filterMin(GetFilterFromString(filterMin)), filterMag(GetFilterFromString(filterMag)) {
    Initialize(fileName);
}

Texture::Texture(void *buffer, size_t bufferSize) {
    Initialize(buffer, bufferSize);
}

Texture::Texture(void *buffer, size_t bufferSize, unsigned int wrapS, unsigned int wrapT, unsigned int filterMin, unsigned int filterMag) :
    wrapS(wrapS), wrapT(wrapT), filterMin(filterMin), filterMag(filterMag) {
    Initialize(buffer, bufferSize);
}

Texture::Texture(void *buffer, size_t bufferSize, const std::string &wrapS, const std::string &wrapT, const std::string &filterMin, const std::string &filterMag) :
    wrapS(GetWrapFromString(wrapS)), wrapT(GetWrapFromString(wrapT)), filterMin(GetFilterFromString(filterMin)), filterMag(GetFilterFromString(filterMag)) {
    Initialize(buffer, bufferSize);
}

Texture::Texture(unsigned int width, unsigned int height, unsigned int colorValue) :
    nrChannels(4),
    width(width),
    height(height) {
    data = new unsigned char[width * height * 4];
    for(int i = 0; i < (int)(width * height * 4); i++) {
        data[i] = colorValue;
    }
    if (IsValid()) {
        Generate();
    } else {
        logger->Error("Failed to load colored texture!");
    }
}

Texture::~Texture() {
    stbi_image_free(this->data);
    this->data = nullptr;
}

void Texture::Initialize(const char* fileName) {
    this->fileName = std::string(fileName);
    // load image, create texture, and generate mipmaps
    stbi_set_flip_vertically_on_load(false);
    this->data = stbi_load(fileName, &width, &height, &nrChannels, 0);
    if(IsValid()) {
        Generate();
    } else {
        logger->Error("Texture failed to load at: " + std::string(fileName));
    }
}

void Texture::Initialize(void *buffer, size_t bufferSize) {
    // load image, create texture, and generate mipmaps
    stbi_set_flip_vertically_on_load(false);
    this->data = stbi_load_from_memory((unsigned char*) buffer, bufferSize, &width, &height, &nrChannels, 0);
    if(IsValid()) {
        Generate();
    } else {
        logger->Error("Texture failed to load at texture from memory!");
    }
}

void Texture::Generate() {
    if (nrChannels == 1) {
        imageFormat = GL_RED;
    } else if (nrChannels == 3) {
        imageFormat = GL_RGB;
    } else if (nrChannels == 4) {
        imageFormat = GL_RGBA;
    }

    // Create texture
    glGenTextures(1, &this->ID);
    Bind();
    glTexImage2D(GL_TEXTURE_2D, 0, this->internalFormat, this->width, this->height, 0, this->imageFormat, GL_UNSIGNED_BYTE, this->data);
    glGenerateMipmap(GL_TEXTURE_2D);
    // Wrap and filter modes
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->wrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->wrapT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->filterMin);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->filterMag);
    // Unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);
}

unsigned int Texture::GetWrapFromString(const std::string &wrap) const {
    if (wrap == "clamp_to_border") {
        return GL_CLAMP_TO_BORDER;
    } else if (wrap == "repeat") {
        return GL_REPEAT;
    }
    logger->Error("'" + wrap + "' is an invalid wrap value!");
    return wrapS;
}

unsigned int Texture::GetFilterFromString(const std::string &filter) const {
    if (filter == "nearest") {
        return GL_NEAREST;
    } else if (filter == "linear") {
        return GL_LINEAR;
    }
    logger->Error("'" + filter + "' is an invalid filter value!");
    return filterMin;
}

void Texture::Bind() const {
    glBindTexture(GL_TEXTURE_2D, this->ID);
    logger->LogOpenGLError("glBindTexture");
}

std::string Texture::GetFilePath() const {
    return fileName;
}

int Texture::GetWidth() const {
    return width;
}

int Texture::GetHeight() const {
    return height;
}

unsigned int Texture::GetImageFormat() const {
    return imageFormat;
}

unsigned char* Texture::GetData() const {
    return data;
}

std::string Texture::GetWrapSString() const {
    if (wrapS == GL_CLAMP_TO_BORDER) {
        return "clamp_to_border";
    } else if (wrapS == GL_REPEAT) {
        return "repeat";
    }
    logger->Error("Not valid wrap s string!");
    return "";
}

std::string Texture::GetWrapTString() const {
    if (wrapT == GL_CLAMP_TO_BORDER) {
        return "clamp_to_border";
    } else if (wrapT == GL_REPEAT) {
        return "repeat";
    }
    logger->Error("Not valid wrap t string!");
    return "";
}

std::string Texture::GetFilterMinString() const {
    if (filterMin == GL_NEAREST) {
        return "nearest";
    } else if (filterMin == GL_LINEAR) {
        return "linear";
    }
    logger->Error("Not valid filter min string string!");
    return "";
}

std::string Texture::GetFilterMagString() const {
    if (filterMin == GL_NEAREST) {
        return "nearest";
    } else if (filterMin == GL_LINEAR) {
        return "linear";
    }
    logger->Error("Not valid filter max string string!");
    return "";
}

bool Texture::IsValid() const {
    if(this->data) {
        return true;
    }
    return false;
}
