#ifndef RENDERER3D_H
#define RENDERER3D_H

#include <glad/glad.h>

#include "texture.h"
#include "shader/shader.h"
#include "../math/vector3.h"

// TODO: Finish 3D Renderer (on the feature list)
struct EntityMaterial {
    Vector3 ambient = Vector3(1.0f, 0.5f, 0.31f);
    Vector3 diffuse = Vector3(1.0f, 0.5f, 0.31f);
    Vector3 specular = Vector3(0.5f, 0.5f, 0.5f);
    float shininess = 32.0f;
};

struct LightEntity {
    GLuint VAO;
    Shader shader;
    Vector3 position = Vector3(1.2f, 1.0f, 2.0f);
    GLfloat scale = 0.2f;
    Color color = Color(1.0f, 1.0f, 1.0f);
    EntityMaterial material = EntityMaterial{
        .ambient = Vector3(1.0f, 0.5f, 0.31f),
        .diffuse = Vector3(1.0f, 0.5f, 0.31f),
        .specular = Vector3(1.0f, 1.0f, 1.0f)
    };
};

struct CubeEntity {
    GLuint VAO;
    Shader shader;
    Color color = Color(1.0f, 0.5f, 0.31f);
    EntityMaterial material;
};

class Renderer3D {
  private:
    GLuint VBO;
    LightEntity light;
    CubeEntity cube;
    float fieldOfView = 45.0f;
    GLfloat vertices[360] = {-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
                             0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
                             0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
                             0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
                             -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
                             -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

                             -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
                             0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
                             0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
                             0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
                             -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
                             -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

                             -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
                             -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
                             -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
                             -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
                             -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
                             -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

                             0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
                             0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
                             0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
                             0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
                             0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
                             0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

                             -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
                             0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
                             0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
                             0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
                             -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
                             -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

                             -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
                             0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
                             0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
                             0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
                             -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
                             -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f // bottom-left
                            };

  public:
    Renderer3D();

    ~Renderer3D();

    void Render();
};

#endif //RENDERER3D_H
