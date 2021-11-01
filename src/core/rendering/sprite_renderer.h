#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include <glad/glad.h>

#include <glm/glm.hpp>

#include "render_context.h"
#include "texture.h"
#include "shader/shader.h"
#include "../color.h"
#include "../math/vector2.h"
#include "../math/rect2.h"
#include "../project_properties.h"

struct SpriteDrawBatch {
    Texture *texture2D = nullptr;
    Rect2 sourceRectangle;
    Rect2 destinationRectangle;
    float rotation = 0.0f;
    Color color = Color(1.0f, 1.0f, 1.0f, 1.0f);
    bool flipX = false;
    bool flipY = false;
};

class SpriteRenderer {
  private:
    RenderContext *renderContext = nullptr;
    Shader shader;
    GLuint quadVAO;
    GLuint quadVBO;
    glm::mat4 projection;
    ProjectProperties *projectProperties = nullptr;
  public:
    SpriteRenderer(RenderContext *renderContext);

    void Draw(Texture *texture2D, Rect2 sourceRectangle, Rect2 destinationRectangle, float rotation = 0.0f, Color color = Color(1.0f, 1.0f, 1.0f, 1.0f), bool flipX = false, bool flipY = false);

    void UpdateProjection();

    glm::mat4 GetProjection() const;
};


#endif //SPRITE_RENDERER_H
