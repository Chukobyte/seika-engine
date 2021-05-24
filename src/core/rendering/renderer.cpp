#include "renderer.h"

#include "../project_properties.h"
#include <glm/gtx/string_cast.hpp>

#define GLM_ENABLE_EXPERIMENTAL

// Sprite Renderer
SpriteRenderer::SpriteRenderer(const glm::mat4 &projection) {
    GLfloat vertices[] = {
        // positions // texture coordinates
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    };

    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);

    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(quadVAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*) nullptr);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    shader = Shader(OPENGL_SHADER_SOURCE_SPRITE);
    shader.Use();
    shader.SetMatrix4Float("projection", projection);
    shader.SetInt("sprite", 0);
}

void SpriteRenderer::Draw(Texture2D *texture2D, Rect2 *sourceRectangle, Rect2 *destinationRectangle, int zIndex, float rotation, Color color, bool flipX, bool flipY) {
    glDepthMask(false);

    Matrix4 model = Matrix4(1.0f);
    std::cout << "Model\n" << model << std::endl;
    model.Set(model.Translation(Vector3(destinationRectangle->x, destinationRectangle->y, 0.0f)));
    std::cout << "After First translation\n" << model << std::endl;
    model.Set(model.Translation(Vector3(0.5f * destinationRectangle->w, 0.5f * destinationRectangle->h, 0.0f)));
    std::cout << "After Second translation\n" << model << std::endl;
    model.Set(model.Rotate(Vector3(0.0f, 0.0f, 1.0f), rotation));
    std::cout << "After rotation\n" << model << std::endl;
    model.Set(model.Translation(Vector3(-0.5f * destinationRectangle->w, -0.5f * destinationRectangle->h, 0.0f)));
    std::cout << "After Third translation\n" << model << std::endl;
    model.Set(model.Scale(Vector3(destinationRectangle->w, destinationRectangle->h, 1.0f)));
    std::cout << "After scale\n" << model << std::endl;

//    glm::mat4 model = glm::mat4(1.0f);
//    std::cout << "Model\n" << glm::to_string(model) << std::endl;
//    model = glm::translate(model, glm::vec3(destinationRectangle->x, destinationRectangle->y, 0.0f));  // first translate (transformations are: scale happens first, then rotation, and then final translation happens; reversed order)
//    std::cout << "After First translation\n" << glm::to_string(model) << std::endl;
//
//    model = glm::translate(model, glm::vec3(0.5f * destinationRectangle->w, 0.5f * destinationRectangle->h, 0.0f)); // move origin of rotation to center of quad
//    std::cout << "After Second translation\n" << glm::to_string(model) << std::endl;
//    model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f)); // then rotate
//    std::cout << "After rotation\n" << glm::to_string(model) << std::endl;
//    model = glm::translate(model, glm::vec3(-0.5f * destinationRectangle->w, -0.5f * destinationRectangle->h, 0.0f)); // move origin back
//    std::cout << "After third translation\n" << glm::to_string(model) << std::endl;
//
//    model = glm::scale(model, glm::vec3(destinationRectangle->w, destinationRectangle->h, 1.0f)); // last scale
//    std::cout << "After scale\n" << glm::to_string(model) << std::endl;

    glBindVertexArray(quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);

    shader.Use();
    shader.SetMatrix4Float("model", model);
    shader.SetVec4Float("spriteColor", color.r, color.g, color.b, color.a);

    glActiveTexture(GL_TEXTURE0);
    texture2D->Bind();

    // render subimage based on source rectangle
    glPixelStorei(GL_UNPACK_ROW_LENGTH, texture2D->width);
    glPixelStorei(GL_UNPACK_SKIP_PIXELS, sourceRectangle->x);
    glPixelStorei(GL_UNPACK_SKIP_ROWS, sourceRectangle->y);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sourceRectangle->w, sourceRectangle->h, 0, texture2D->imageFormat, GL_UNSIGNED_BYTE, texture2D->data);

    glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);
    glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);

    // Render Container
    GLfloat vertices[6][4] = {
        // positions // texture coordinates
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    };

    static const int VERT_X = 2;
    static const int VERT_Y = 3;
    if (flipX) {
        vertices[0][VERT_X] = 1.0f;
        vertices[1][VERT_X] = 0.0f;
        vertices[2][VERT_X] = 1.0f;
        vertices[3][VERT_X] = 1.0f;
        vertices[4][VERT_X] = 0.0f;
        vertices[5][VERT_X] = 0.0f;
    }

    if (flipY) {
        vertices[0][VERT_Y] = 0.0f;
        vertices[1][VERT_Y] = 1.0f;
        vertices[2][VERT_Y] = 1.0f;
        vertices[3][VERT_Y] = 0.0f;
        vertices[4][VERT_Y] = 0.0f;
        vertices[5][VERT_Y] = 1.0f;
    }

    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glBindVertexArray(0);
    glDepthMask(true);
}

void SpriteRenderer::UpdateProjection(const glm::mat4 &projection) {
    shader.Use();
    shader.SetMatrix4Float("projection", projection);
}

// Font Renderer
FontRenderer::FontRenderer() {
    shader = Shader(OPENGL_SHADER_SOURCE_FONT);
    UpdateProjection();
}

void FontRenderer::Draw(Font *font, const std::string &text, float x, float y, float scale, const Color color) {
    Vector2 currentScale = Vector2(scale, scale);
    shader.Use();
    shader.SetVec4Float("textColor", color);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(font->VAO);

    ProjectProperties *projectProperties = ProjectProperties::GetInstance();
    y = ConvertMinMax(y, static_cast<float>(projectProperties->windowWidth), 0, 0, static_cast<float>(projectProperties->windowHeight));

    // iterate through all characters
    std::string::const_iterator c;
    for(c = text.begin(); c != text.end(); c++) {
        Character ch = font->characters[*c];

        float xPos = x + ch.bearing.x * currentScale.x;
        float yPos = y - (ch.size.y) * currentScale.y;

        float w = ch.size.x * currentScale.x;
        float h = ch.size.y * currentScale.y;
        // update VBO for each character
        GLfloat vertices[6][4] = {
            {xPos,     yPos + h, 0.0f, 0.0f},
            {xPos,     yPos,     0.0f, 1.0f},
            {xPos + w, yPos,     1.0f, 1.0f},

            {xPos,     yPos + h, 0.0f, 0.0f},
            {xPos + w, yPos,     1.0f, 1.0f},
            {xPos + w, yPos + h, 1.0f, 0.0f}
        };
        // render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.textureID);
        // update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, font->VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // advance cursor for next glyph (note that advance is number of 1/64 pixels)
        x += (ch.advance >> 6) * currentScale.x; // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void FontRenderer::UpdateProjection() {
    ProjectProperties *projectProperties = ProjectProperties::GetInstance();
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(projectProperties->windowWidth), 0.0f, static_cast<float>(projectProperties->windowHeight));
    shader.Use();
    shader.SetMatrix4Float("projection", projection);
}

// Renderer

Renderer::~Renderer() {
    delete spriteRenderer;
    delete fontRenderer;
}

void Renderer::Initialize() {
    // OpenGL State
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    ProjectProperties *projectProperties = ProjectProperties::GetInstance();
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(projectProperties->windowWidth), static_cast<float>(projectProperties->windowHeight), 0.0f, -1.0f, 1.0f);
    spriteRenderer = new SpriteRenderer(projection);
    fontRenderer = new FontRenderer();
}

void Renderer::DrawSprite(Texture2D *texture2D, Rect2 *sourceRectangle, Rect2 *destinationRectangle, int zIndex, float rotation, Color color, bool flipX, bool flipY) {
    spriteRenderer->Draw(texture2D, sourceRectangle, destinationRectangle, zIndex, rotation, color, flipX, flipY);
}

void Renderer::DrawFont(Font *font, const std::string &text, float x, float y, float scale, Color color) {
    fontRenderer->Draw(font, text, x, y, scale, color);
}
