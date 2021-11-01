#include "renderer2d.h"

#include "../project_properties.h"

Renderer2D::Renderer2D(RenderContext *renderContext) : renderContext(renderContext) {}

Renderer2D::~Renderer2D() {
    delete spriteRenderer;
    delete fontRenderer;
}

void Renderer2D::AddFontToBatch(FontDrawBatch fontDrawBatch, int zIndex) {
    if (!HasDrawBatchIndex(zIndex)) {
        drawBatches2D.emplace(zIndex, ZIndexDrawBatch{});
    }
    drawBatches2D[zIndex].fontDrawBatches.emplace_back(fontDrawBatch);
}

void Renderer2D::AddSpriteToBatch(SpriteDrawBatch spriteDrawBatch, int zIndex) {
    if (!HasDrawBatchIndex(zIndex)) {
        drawBatches2D.emplace(zIndex, ZIndexDrawBatch{});
    }
    drawBatches2D[zIndex].spriteDrawBatches.emplace_back(spriteDrawBatch);
}

bool Renderer2D::HasDrawBatchIndex(int zIndex) const {
    return drawBatches2D.count(zIndex) > 0;
}

void Renderer2D::Initialize() {
    // OpenGL State
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    ProjectProperties *projectProperties = ProjectProperties::GetInstance();
    spriteRenderer = new SpriteRenderer(renderContext);
    fontRenderer = new FontRenderer(renderContext);
}

void Renderer2D::UpdateProjection() {
    fontRenderer->UpdateProjection();
    spriteRenderer->UpdateProjection();
}

void Renderer2D::DrawSprite(Texture *texture2D, Rect2 sourceRectangle, Rect2 destinationRectangle, float rotation, Color color, bool flipX, bool flipY) {
    spriteRenderer->Draw(texture2D, sourceRectangle, destinationRectangle, rotation, color, flipX, flipY);
}

void Renderer2D::DrawFont(Font *font, const std::string &text, float x, float y, float scale, Color color) {
    fontRenderer->Draw(font, text, x, y, scale, color);
}

void Renderer2D::BatchDrawSprite(Texture *texture2D, Rect2 sourceRectangle, Rect2 destinationRectangle, int zIndex, float rotation, Color color, bool flipX, bool flipY) {
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

void Renderer2D::BatchDrawFont(Font *font, const std::string &text, float x, float y, int zIndex, float scale, Color color) {
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

void Renderer2D::FlushBatches() {
    glDisable(GL_DEPTH_TEST);
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

glm::mat4 Renderer2D::GetProjection() const {
    return spriteRenderer->GetProjection();
}
