#ifndef RENDERER3D_H
#define RENDERER3D_H

#include <glad/glad.h>

#include "texture.h"
#include "shader/shader.h"
#include "../math/vector3.h"

class Renderer3D {
  private:
    GLuint VBO;
    GLuint VAO;
    Shader shader;
    Texture *awesomeFaceTexture = nullptr;
    Texture *containerTexture = nullptr;
    float fieldOfView = 45.0f;
    GLfloat vertices[180] = {-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // Back face , bottom-left
                             0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
                             0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // bottom-right
                             0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
                             -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // bottom-left
                             -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
                             // Front face
                             -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
                             0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
                             0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
                             0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
                             -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, // top-left
                             -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
                             // Left face
                             -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-right
                             -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-left
                             -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left
                             -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left
                             -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right
                             -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-right
                             // Right face
                             0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-left
                             0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-right
                             0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
                             0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-right
                             0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-left
                             0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
                             // Bottom face
                             -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
                             0.5f, -0.5f, -0.5f,  1.0f, 1.0f, // top-left
                             0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
                             0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
                             -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right
                             -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
                             // Top face
                             -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
                             0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
                             0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
                             0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
                             -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
                             -0.5f,  0.5f,  0.5f,  0.0f, 0.0f  // bottom-left
                            };

    Vector3 cubePositions[10] = {Vector3(0.0f, 0.0f, 0.0f),
                                 Vector3(2.0f, 5.0f, -15.0f),
                                 Vector3(-1.5f, -2.2f, -2.5f),
                                 Vector3(-3.8f, -2.0f, -12.3f),
                                 Vector3(-2.4f, -0.4f, -3.5f),
                                 Vector3(-1.7f, 3.0f, -7.5f),
                                 Vector3(1.3f, -2.0f, -2.5f),
                                 Vector3(1.5f, 2.0f, -2.5f),
                                 Vector3(1.5f, 0.2f, -1.5f),
                                 Vector3(-1.3f, 1.0f, -1.5f)
                                };

  public:
    Renderer3D();

    ~Renderer3D();

    void Render();
};

#endif //RENDERER3D_H
