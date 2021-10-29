#ifndef FONT_RENDERER_H
#define FONT_RENDERER_H

#include <glad/glad.h>

#include <glm/glm.hpp>

#include "render_context.h"
#include "shader/shader.h"
#include "../color.h"
#include "../math/vector2.h"
#include "../math/rect2.h"
#include "font.h"
#include "../project_properties.h"

struct FontDrawBatch {
    Font *font = nullptr;
    std::string text = "";
    float x = 0.0f;
    float y = 0.0f;
    float scale = 1.0f;
    Color color = Color(1.0f, 1.0f, 1.0f, 1.0f);
};

class FontRenderer {
  private:
    RenderContext *renderContext = nullptr;
    Shader shader;
    ProjectProperties *projectProperties = nullptr;

    static float ConvertMinMax(float input, float inputLow, float inputHigh, float outputLow, float outputHigh) {
        return (((input - inputLow) / (inputHigh - inputLow)) * (outputHigh - outputLow) + outputLow);
    }
  public:
    FontRenderer(RenderContext *renderContext);

    void Draw(Font *font, const std::string &text, float x, float y, float scale = 1.0f, const Color color = Color(1.0f, 1.0f, 1.0f, 1.0f));

    void UpdateProjection();
};


#endif //FONT_RENDERER_H
