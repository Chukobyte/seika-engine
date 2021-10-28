#include "renderer.h"

#include "../project_properties.h"

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

void SpriteRenderer::Draw(Texture *texture2D, Rect2 sourceRectangle, Rect2 destinationRectangle, float rotation, Color color, bool flipX, bool flipY) {
    glDepthMask(false);

    // 1. Translation
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(destinationRectangle.x, destinationRectangle.y, 0.0f));  // first translate (transformations are: scale happens first, then rotation, and then final translation happens; reversed order)
    // 2. Rotation
    model = glm::translate(model, glm::vec3(0.5f * destinationRectangle.w, 0.5f * destinationRectangle.h, 0.0f)); // move origin of rotation to center of quad
    model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f)); // then rotate
    model = glm::translate(model, glm::vec3(-0.5f * destinationRectangle.w, -0.5f * destinationRectangle.h, 0.0f)); // move origin back
    // 3. Scaling
    model = glm::scale(model, glm::vec3(destinationRectangle.w, destinationRectangle.h, 1.0f)); // last scale

    glBindVertexArray(quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);

    shader.Use();
    shader.SetMatrix4Float("model", model);
    shader.SetVec4Float("spriteColor", color.r, color.g, color.b, color.a);

    glActiveTexture(GL_TEXTURE0);
    texture2D->Bind();

    // render subimage based on source rectangle
    glPixelStorei(GL_UNPACK_ROW_LENGTH, texture2D->GetWidth());
    glPixelStorei(GL_UNPACK_SKIP_PIXELS, sourceRectangle.x);
    glPixelStorei(GL_UNPACK_SKIP_ROWS, sourceRectangle.y);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sourceRectangle.w, sourceRectangle.h, 0, texture2D->GetImageFormat(), GL_UNSIGNED_BYTE, texture2D->GetData());

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
    y += 64.0f;
    y = ConvertMinMax(y, static_cast<float>(projectProperties->windowWidth), 0, 0, static_cast<float>(projectProperties->windowHeight));

    // iterate through all characters
    std::string::const_iterator c;
    for(c = text.begin(); c != text.end(); c++) {
        Character ch = font->characters[*c];

        const float xPos = x + (ch.bearing.x * currentScale.x);
        const float yPos = y - (ch.size.y - ch.bearing.y) * currentScale.y;

        const float w = ch.size.x * currentScale.x;
        const float h = ch.size.y * currentScale.y;
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
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    ProjectProperties *projectProperties = ProjectProperties::GetInstance();
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(projectProperties->windowWidth), static_cast<float>(projectProperties->windowHeight), 0.0f, -1.0f, 1.0f);
    spriteRenderer = new SpriteRenderer(projection);
    fontRenderer = new FontRenderer();
}

void Renderer::DrawSprite(Texture *texture2D, Rect2 sourceRectangle, Rect2 destinationRectangle, float rotation, Color color, bool flipX, bool flipY) {
    spriteRenderer->Draw(texture2D, sourceRectangle, destinationRectangle, rotation, color, flipX, flipY);
}

void Renderer::DrawFont(Font *font, const std::string &text, float x, float y, float scale, Color color) {
    fontRenderer->Draw(font, text, x, y, scale, color);
}

void Renderer::BatchDrawSprite(Texture *texture2D, Rect2 sourceRectangle, Rect2 destinationRectangle, int zIndex, float rotation, Color color, bool flipX, bool flipY) {
    AddSpriteToBatch(SpriteDrawBatch{
        .texture2D = texture2D,
        .sourceRectangle = sourceRectangle,
        .destinationRectangle = destinationRectangle,
        .rotation = rotation,
        .color = color,
        .flipX = flipX,
        .flipY = flipY
    },
    zIndex);
}

void Renderer::BatchDrawFont(Font *font, const std::string &text, float x, float y, int zIndex, float scale, Color color) {
    AddFontToBatch(FontDrawBatch{
        .font = font,
        .text = text,
        .x = x,
        .y = y,
        .scale = scale,
        .color = color
    },
    zIndex);
}

void Renderer::FlushBatches() {
    glDepthMask(GL_FALSE);
    for (const auto &pair : drawBatches2D) {
        ZIndexDrawBatch zIndexDrawBatch = pair.second;
        for (const FontDrawBatch &fontDrawBatch : zIndexDrawBatch.fontDrawBatches) {
            fontRenderer->Draw(fontDrawBatch.font, fontDrawBatch.text, fontDrawBatch.x, fontDrawBatch.y, fontDrawBatch.scale, fontDrawBatch.color);
        }
        for (const SpriteDrawBatch &spriteDrawBatch : zIndexDrawBatch.spriteDrawBatches) {
            spriteRenderer->Draw(spriteDrawBatch.texture2D, spriteDrawBatch.sourceRectangle, spriteDrawBatch.destinationRectangle, spriteDrawBatch.rotation, spriteDrawBatch.color, spriteDrawBatch.flipX, spriteDrawBatch.flipY);
        }
    }
    drawBatches2D.clear();
}