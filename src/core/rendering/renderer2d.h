#ifndef RENDERER_2D_H
#define RENDERER_2D_H

#include <vector>
#include <map>

#include "sprite_renderer.h"
#include "font_renderer.h"

struct ZIndexDrawBatch {
    std::vector<FontDrawBatch> fontDrawBatches;
    std::vector<SpriteDrawBatch> spriteDrawBatches;
};

class Renderer2D {
  private:
    RenderContext *renderContext = nullptr;
    SpriteRenderer *spriteRenderer = nullptr;
    FontRenderer *fontRenderer = nullptr;
    std::map<int, ZIndexDrawBatch> drawBatches2D;

    void AddFontToBatch(FontDrawBatch fontDrawBatch, int zIndex);

    void AddSpriteToBatch(SpriteDrawBatch spriteDrawBatch, int zIndex);

    bool HasDrawBatchIndex(int zIndex) const;
  public:
    Renderer2D(RenderContext *renderContext);

    ~Renderer2D();

    void Initialize();

    void UpdateProjection();

    void DrawSprite(Texture *texture2D, Rect2 sourceRectangle, Rect2 destinationRectangle, float rotation = 0.0f, Color color = Color(1.0f, 1.0f, 1.0f, 1.0f), bool flipX = false, bool flipY = false);

    void DrawFont(Font *font, const std::string &text, float x, float y, float scale = 1.0f, Color color = Color(1.0f, 1.0f, 1.0f, 1.0f));

    void BatchDrawSprite(Texture *texture2D, Rect2 sourceRectangle, Rect2 destinationRectangle, int zIndex = 0, float rotation = 0.0f, Color color = Color(1.0f, 1.0f, 1.0f, 1.0f), bool flipX = false, bool flipY = false);

    void BatchDrawFont(Font *font, const std::string &text, float x, float y, int zIndex = 0, float scale = 1.0f, Color color = Color(1.0f, 1.0f, 1.0f, 1.0f));

    void FlushBatches();

    glm::mat4 GetProjection() const;
};


#endif //RENDERER_2D_H
