#include "texture.h"

#include <stb_image/stb_image.h>

Logger *Texture::logger = Logger::GetInstance();

Texture::Texture(const char* fileName) {
    Initialize(fileName);
}

Texture::Texture(const char* fileName, unsigned int wrapS, unsigned int wrapT, unsigned int filterMax, unsigned int filterMin) :
    wrapS(wrapS), wrapT(wrapT), filterMax(filterMax), filterMin(filterMin) {
    Initialize(fileName);
}

Texture::Texture(void *buffer, size_t bufferSize) {
    Initialize(buffer, bufferSize);
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
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->filterMax);
    // Unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);
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

bool Texture::IsValid() const {
    if(this->data) {
        return true;
    }
    return false;
}
