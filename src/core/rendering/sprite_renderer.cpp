#include "sprite_renderer.h"

SpriteRenderer::SpriteRenderer(RenderContext *renderContext) : renderContext(renderContext) {
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
    shader.SetInt("sprite", 0);
    UpdateProjection();
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

void SpriteRenderer::UpdateProjection() {
    shader.Use();
//    glm::mat4 projection = glm::ortho(0.0f, renderContext->currentWindowWidth, renderContext->currentWindowHeight, 0.0f, -1.0f, 1.0f);
    glm::mat4 projection = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);
    shader.SetMatrix4Float("projection", projection);
}
