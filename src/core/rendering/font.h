#ifndef FONT_H
#define FONT_H

#include <iostream>

#include <string>
#include <map>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <glad/glad.h>

#include "../math/vector2.h"

#include "../utils/file_helper.h"
#include "../utils/logger.h"

struct Character {
    GLuint textureID;
    IVector2 size;
    IVector2 bearing;
    unsigned int advance;
};

class Font {
  private:
    bool valid = false;
    std::string uid;
    std::string filePath;
    int size;
    long height;

    void ConfigureVertex() {
        // configure VAO & VBO texture quads
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), nullptr);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
  public:
    std::map<GLchar, Character> characters;
    GLuint VAO;
    GLuint VBO;

    Font(const std::string &uid, FT_Library freeTypeLibrary, const char* fileName, int size) {
        this->uid = uid;
        this->filePath = std::string(fileName);
        this->size = size;
        LoadFont(freeTypeLibrary, fileName, size);
        ConfigureVertex();
    }

    Font(const std::string &uid, FT_Library freeTypeLibrary, const char* fileName, int size, void *buffer, size_t bufferSize) {
        this->uid = uid;
        this->filePath = std::string(fileName);
        this->size = size;
        LoadFontFromMemory(freeTypeLibrary, buffer, bufferSize, size);
        ConfigureVertex();
    }

    void LoadFont(FT_Library freeTypeLibrary, const char* fileName, int size) {
        static Logger *logger = Logger::GetInstance();
        if(!FileHelper::DoesFileExist(fileName)) {
            logger->Error("Freetype failed at path: " + std::string(fileName));
        }
        FT_Face face;
        if(FT_New_Face(freeTypeLibrary, fileName, 0, &face)) {
            logger->Error("Freetype failed to load font!");
        } else {
            // set size to load glyphs. width set to 0 to dynamically adjust
            FT_Set_Pixel_Sizes(face, 0, size);

            height = face->size->metrics.height / face->size->metrics.y_ppem;
//            height = face->size->metrics.height;

            // disable byte-alignment restriction
            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

            // load first 128 characters of ASCII set
            for(unsigned char c = 0; c < 128; c++) {
                // load character glyph
                if(FT_Load_Char(face, c, FT_LOAD_RENDER)) {
                    logger->Error("Freetype Failed to load Glyph");
                    continue;
                }
                // generate texture
                unsigned int textTexture;
                glGenTextures(1, &textTexture);
                glBindTexture(GL_TEXTURE_2D, textTexture);
                glTexImage2D(
                    GL_TEXTURE_2D,
                    0,
                    GL_RED,
                    face->glyph->bitmap.width,
                    face->glyph->bitmap.rows,
                    0,
                    GL_RED,
                    GL_UNSIGNED_BYTE,
                    face->glyph->bitmap.buffer
                );
                // set texture options
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                // store character for later use
                Character character = {
                    .textureID = textTexture,
                    .size = IVector2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                    .bearing = IVector2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                    .advance = static_cast<unsigned int>(face->glyph->advance.x)
                };
                characters.insert(std::pair<char, Character>(c, character));
            }
            glBindTexture(GL_TEXTURE_2D, 0);
            valid = true;
        }
        FT_Done_Face(face);
    }

    void LoadFontFromMemory(FT_Library freeTypeLibrary, void *buffer, size_t bufferSize, int size) {
        static Logger *logger = Logger::GetInstance();
        FT_Face face;
        if(FT_New_Memory_Face(freeTypeLibrary, (unsigned char*) buffer, bufferSize, 0, &face)) {
            logger->Error("Freetype failed to load font!");
        } else {
            // set size to load glyphs. width set to 0 to dynamically adjust
            FT_Set_Pixel_Sizes(face, 0, size);

            height = face->size->metrics.height / face->size->metrics.y_ppem;

            // disable byte-alignment restriction
            glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

            // load first 128 characters of ASCII set
            for(unsigned char c = 0; c < 128; c++) {
                // load character glyph
                if(FT_Load_Char(face, c, FT_LOAD_RENDER)) {
                    logger->Error("Freetype Failed to load Glyph");
                    continue;
                }
                // generate texture
                unsigned int textTexture;
                glGenTextures(1, &textTexture);
                glBindTexture(GL_TEXTURE_2D, textTexture);
                glTexImage2D(
                    GL_TEXTURE_2D,
                    0,
                    GL_RED,
                    face->glyph->bitmap.width,
                    face->glyph->bitmap.rows,
                    0,
                    GL_RED,
                    GL_UNSIGNED_BYTE,
                    face->glyph->bitmap.buffer
                );
                // set texture options
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                // store character for later use
                Character character = {
                    .textureID = textTexture,
                    .size = IVector2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                    .bearing = IVector2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                    .advance = static_cast<unsigned int>(face->glyph->advance.x)
                };
                characters.insert(std::pair<char, Character>(c, character));
            }
            glBindTexture(GL_TEXTURE_2D, 0);
            valid = true;
        }
        FT_Done_Face(face);
    }

    bool IsValid() const {
        return valid;
    }

    std::string GetUID() const {
        return uid;
    }

    std::string GetFilePath() const {
        return filePath;
    }

    int GetSize() const {
        return size;
    }

    long GetHeight() const {
        return height;
    }
};

#endif //FONT_H
