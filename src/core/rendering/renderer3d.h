#ifndef RENDERER3D_H
#define RENDERER3D_H

#include <glad/glad.h>

#include "texture.h"
#include "shader/shader.h"
#include "../math/vector3.h"

// TODO: Finish 3D Renderer (on the feature list)
struct LightEntity {
    GLuint VAO;
    Shader shader;
    Vector3 position = Vector3(1.2f, 1.0f, 2.0f);
    GLfloat scale = 0.2f;
    Color color = Color(1.0f, 1.0f, 1.0f);
};

struct CubeEntity {
    GLuint VAO;
    Shader shader;
    Color color = Color(1.0f, 0.5f, 0.31f);
};

class Renderer3D {
  private:
    GLuint VBO;
    LightEntity light;
    CubeEntity cube;
    float fieldOfView = 45.0f;
    GLfloat vertices[360] = {-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, // Back face , bottom-left
                             0.5f,  0.5f, -0.5f, 0.0f, 0.0f, -1.0f, // top-right
                             0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, // bottom-right
                             0.5f,  0.5f, -0.5f, 0.0f, 0.0f, -1.0f, // top-right
                             -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, // bottom-left
                             -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, -1.0f, // top-left
                             // Front face
                             -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, -1.0f, // bottom-left
                             0.5f, -0.5f,  0.5f, 0.0f, 0.0f, -1.0f, // bottom-right
                             0.5f,  0.5f,  0.5f, 0.0f, 0.0f, -1.0f, // top-right
                             0.5f,  0.5f,  0.5f, 0.0f, 0.0f, -1.0f, // top-right
                             -0.5f,  0.5f,  0.5f, 0.0f, 0.0f, -1.0f, // top-left
                             -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, -1.0f, // bottom-left
                             // Left face
                             -0.5f,  0.5f,  0.5f, -1.0f, 0.0f, 0.0f, // top-right
                             -0.5f,  0.5f, -0.5f, -1.0f, 0.0f, 0.0f, // top-left
                             -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, // bottom-left
                             -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, // bottom-left
                             -0.5f, -0.5f,  0.5f, -1.0f, 0.0f, 0.0f, // bottom-right
                             -0.5f,  0.5f,  0.5f, -1.0f, 0.0f, 0.0f, // top-right
                             // Right face
                             0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f, // top-left
                             0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, // bottom-right
                             0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 0.0f, // top-right
                             0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, // bottom-right
                             0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 0.0f, // top-left
                             0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 0.0f, // bottom-left
                             // Bottom face
                             -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, // top-right
                             0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, // top-left
                             0.5f, -0.5f,  0.5f, 0.0f, -1.0f, 0.0f, // bottom-left
                             0.5f, -0.5f,  0.5f, 0.0f, -1.0f, 0.0f, // bottom-left
                             -0.5f, -0.5f,  0.5f, 0.0f, -1.0f, 0.0f, // bottom-right
                             -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, // top-right
                             // Top face
                             -0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // top-left
                             0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f, // bottom-right
                             0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // top-right
                             0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f, // bottom-right
                             -0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // top-left
                             -0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f // bottom-left
                            };

  public:
    Renderer3D();

    ~Renderer3D();

    void Render();
};

#endif //RENDERER3D_H
