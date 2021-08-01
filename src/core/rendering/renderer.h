#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <map>

#include <glad/glad.h>

#include <glm/glm.hpp>

#include "texture.h"
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

    void Draw(Texture *texture2D, Rect2 sourceRectangle, Rect2 destinationRectangle, float rotation = 0.0f, Color color = Color(1.0f, 1.0f, 1.0f, 1.0f), bool flipX = false, bool flipY = false);

    void UpdateProjection(const glm::mat4 &projection);
};

class FontRenderer {
  private:
    Shader shader;
    static float ConvertMinMax(float input, float inputLow, float inputHigh, float outputLow, float outputHigh) {
        return (((input - inputLow) / (inputHigh - inputLow)) * (outputHigh - outputLow) + outputLow);
    }
  public:
    FontRenderer();

    void Draw(Font *font, const std::string &text, float x, float y, float scale = 1.0f, const Color color = Color(1.0f, 1.0f, 1.0f, 1.0f));

    void UpdateProjection();
};

struct SpriteDrawBatch {
    Texture *texture2D = nullptr;
    Rect2 sourceRectangle;
    Rect2 destinationRectangle;
    float rotation = 0.0f;
    Color color = Color(1.0f, 1.0f, 1.0f, 1.0f);
    bool flipX = false;
    bool flipY = false;
};

struct FontDrawBatch {
    Font *font = nullptr;
    std::string text;
    float x = 0.0f;
    float y = 0.0f;
    float scale = 1.0f;
    Color color = Color(1.0f, 1.0f, 1.0f, 1.0f);
};

struct ZIndexDrawBatch {
    std::vector<FontDrawBatch> fontDrawBatches;
    std::vector<SpriteDrawBatch> spriteDrawBatches;
};

class Renderer {
  private:
    SpriteRenderer *spriteRenderer = nullptr;
    FontRenderer *fontRenderer = nullptr;
    std::map<int, ZIndexDrawBatch> drawBatches2D;

    void AddFontToBatch(FontDrawBatch fontDrawBatch, int zIndex) {
        if (!HasDrawBatchIndex(zIndex)) {
            drawBatches2D.emplace(zIndex, ZIndexDrawBatch{});
        }
        drawBatches2D[zIndex].fontDrawBatches.emplace_back(fontDrawBatch);
    }

    void AddSpriteToBatch(SpriteDrawBatch spriteDrawBatch, int zIndex) {
        if (!HasDrawBatchIndex(zIndex)) {
            drawBatches2D.emplace(zIndex, ZIndexDrawBatch{});
        }
        drawBatches2D[zIndex].spriteDrawBatches.emplace_back(spriteDrawBatch);
    }

    bool HasDrawBatchIndex(int zIndex) {
        return drawBatches2D.count(zIndex) > 0;
    }
  public:
    Renderer() = default;

    ~Renderer();

    void Initialize();

    void DrawSprite(Texture *texture2D, Rect2 sourceRectangle, Rect2 destinationRectangle, float rotation = 0.0f, Color color = Color(1.0f, 1.0f, 1.0f, 1.0f), bool flipX = false, bool flipY = false);

    void DrawFont(Font *font, const std::string &text, float x, float y, float scale = 1.0f, Color color = Color(1.0f, 1.0f, 1.0f, 1.0f));

    void BatchDrawSprite(Texture *texture2D, Rect2 sourceRectangle, Rect2 destinationRectangle, int zIndex = 0, float rotation = 0.0f, Color color = Color(1.0f, 1.0f, 1.0f, 1.0f), bool flipX = false, bool flipY = false);

    void BatchDrawFont(Font *font, const std::string &text, float x, float y, int zIndex = 0, float scale = 1.0f, Color color = Color(1.0f, 1.0f, 1.0f, 1.0f));

    void FlushBatches();
};


#endif //RENDERER_H
