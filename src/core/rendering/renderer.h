#ifndef RENDERER_H
#define RENDERER_H

#include <glad/glad.h>

#include <glm/glm.hpp>

#include "texture2d.h"
#include "font.h"
#include "shader/shader.h"
#include "../color.h"
#include "../math/vector2.h"
#include "../math/rect2.h"

// TODO: separate renderers into separate files...

class SpriteRenderer {
  private:
    Shader shader;
    GLuint quadVAO;
    GLuint quadVBO;
  public:
    SpriteRenderer(const glm::mat4 &projection);

    void Draw(Texture2D *texture2D, Rect2 *sourceRectangle, Rect2 *destinationRectangle, int zIndex, float rotation = 0.0f, Color color = Color(1.0f, 1.0f, 1.0f, 1.0f));

    void UpdateProjection(const glm::mat4 &projection);
};

class FontRenderer {
  private:
    Shader shader;
    static float ConvertMinMax(float input, float inputLow, float inputHigh, float outputLow, float outputHigh) {
        return (((input - inputLow) / (inputHigh - inputLow)) * (outputHigh - outputLow) + outputLow);
    }
  public:
    FontRenderer(const glm::mat4 &projection);

    void Draw(Font *font, const std::string &text, float x, float y, float scale = 1.0f, const Color color = Color(1.0f, 1.0f, 1.0f, 1.0f));

    void UpdateProjection(const glm::mat4 &projection);
};

struct RendererDrawTarget2D {
    float x;
    float y;
    glm::mat4 model;
    Color color;
};

class Renderer {
  private:
    SpriteRenderer *spriteRenderer = nullptr;
    FontRenderer *fontRenderer = nullptr;
  public:
    Renderer() = default;

    ~Renderer();

    void Initialize(int windowWidth, int windowHeight);

    void DrawSprite(Texture2D *texture2D, Rect2 *sourceRectangle, Rect2 *destinationRectangle, int zIndex, float rotation = 0.0f, Color color = Color(1.0f, 1.0f, 1.0f, 1.0f));

    void DrawFont(Font *font, const std::string &text, float x, float y, float scale = 1.0f, Color color = Color(1.0f, 1.0f, 1.0f, 1.0f));
};


#endif //RENDERER_H
