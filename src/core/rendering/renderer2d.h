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
    Renderer2D(RenderContext *renderContext);

    ~Renderer2D();

    void Initialize();

    void UpdateProjection();

    void DrawSprite(Texture *texture2D, Rect2 sourceRectangle, Rect2 destinationRectangle, float rotation = 0.0f, Color color = Color(1.0f, 1.0f, 1.0f, 1.0f), bool flipX = false, bool flipY = false);

    void DrawFont(Font *font, const std::string &text, float x, float y, float scale = 1.0f, Color color = Color(1.0f, 1.0f, 1.0f, 1.0f));

    void BatchDrawSprite(Texture *texture2D, Rect2 sourceRectangle, Rect2 destinationRectangle, int zIndex = 0, float rotation = 0.0f, Color color = Color(1.0f, 1.0f, 1.0f, 1.0f), bool flipX = false, bool flipY = false);

    void BatchDrawFont(Font *font, const std::string &text, float x, float y, int zIndex = 0, float scale = 1.0f, Color color = Color(1.0f, 1.0f, 1.0f, 1.0f));

    void FlushBatches();
};


#endif //RENDERER_2D_H
