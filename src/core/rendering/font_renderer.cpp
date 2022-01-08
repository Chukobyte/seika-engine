#include "font_renderer.h"

FontRenderer::FontRenderer(RenderContext *renderContext) : renderContext(renderContext) {
    shader = Shader(OPENGL_SHADER_SOURCE_FONT);
    projectProperties = ProjectProperties::GetInstance();
    UpdateProjection();
}

void FontRenderer::Draw(Font *font, const std::string &text, float x, float y, float scale, const Color color) {
    Vector2 currentScale = Vector2(scale, scale);
    shader.Use();
    shader.SetVec4Float("textColor", color);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(font->VAO);

    y = ConvertMinMax(y,
                      static_cast<float>(projectProperties->resolutionHeight),
                      0,
                      0,
                      static_cast<float>(projectProperties->resolutionHeight));
    y -= font->GetSize() * 0.8f;

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
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(projectProperties->resolutionWidth), 0.0f, static_cast<float>(projectProperties->resolutionHeight), -1.0f, 1.0f);
    shader.Use();
    shader.SetMatrix4Float("projection", projection);
}
