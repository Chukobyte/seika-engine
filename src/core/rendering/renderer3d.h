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
    float shininess = 64.0f;
    Texture *diffuseMap = nullptr;
    Texture *specularMap = nullptr;
};

struct LightEntity {
    GLuint VAO;
    Shader shader;
    Vector3 position = Vector3(1.2f, 1.0f, 2.0f);
    Vector3 direction = Vector3(-0.2f, -1.0f, -0.3f);
    GLfloat scale = 0.2f;
    Color color = Color(1.0f, 1.0f, 1.0f);
    EntityMaterial material = EntityMaterial{
        .ambient = Vector3(1.0f, 0.5f, 0.31f),
        .diffuse = Vector3(1.0f, 0.5f, 0.31f),
        .specular = Vector3(1.0f, 1.0f, 1.0f)
    };
    float linear = 0.09f;
    float quadratic = 0.032f;
    const float constant = 1.0f;
    // In Radians
    float cutoff = 12.5f;
    float outerCutoff = 17.5f;
};

struct CubeEntity {
    GLuint VAO;
    Shader shader;
    Color color = Color(1.0f, 0.5f, 0.31f);
    EntityMaterial material;
};

struct DirectionalLight {
    Vector3 direction = Vector3(-0.2f, -1.0f, -0.3f);
    Vector3 ambient = Vector3(0.05f, 0.05f, 0.05f);
    Vector3 diffuse = Vector3(0.4f, 0.4f, 0.4f);
    Vector3 specular = Vector3(0.5f, 0.5f, 0.5f);
};

struct PointLight {
    Vector3 position = Vector3(0.0f);
    Vector3 ambient = Vector3(0.05f, 0.05f, 0.05f);
    Vector3 diffuse = Vector3(0.8f, 0.8f, 0.8f);
    Vector3 specular = Vector3(1.0f, 1.0f, 1.0f);
    float linear = 0.09f;
    float quadratic = 0.032f;
    Vector3 scale = Vector3(0.2f);
    const float constant = 1.0f;
};

struct SpotLight {
    Vector3 position = Vector3(0.0f);
    Vector3 direction = Vector3(0.0f);
    Vector3 ambient = Vector3(0.0f);
    Vector3 diffuse = Vector3(1.0f);
    Vector3 specular = Vector3(1.0f);
    float linear = 0.09f;
    float quadratic = 0.032f;
    const float constant = 1.0f;
    // In Radians
    float cutoff = 12.5f;
    float outerCutoff = 15.0f;
};

class Renderer3D {
  private:
    GLuint VBO;
    LightEntity light;
    CubeEntity cube;
    float fieldOfView = 45.0f;
    // position           //normals            // texture coords
    GLfloat vertices[360] = {-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
                             0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
                             0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
                             0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
                             -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
                             -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

                             -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
                             0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
                             0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
                             0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
                             -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
                             -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

                             -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
                             -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
                             -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
                             -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
                             -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
                             -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

                             0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
                             0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
                             0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
                             0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
                             0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
                             0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

                             -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
                             0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
                             0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
                             0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
                             -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
                             -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

                             -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
                             0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
                             0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
                             0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
                             -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
                             -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
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
//    const unsigned int POINT_LIGHT_AMOUNT = 4;
//    Vector3 pointLightPositions[4] = {Vector3(0.7f, 0.2f, 2.0f),
//                                      Vector3(2.3f, -3.3f, -4.0f),
//                                      Vector3(-4.0f, 2.0f, -12.0f),
//                                      Vector3(0.0f, 0.0f, -3.0f)
//                                     };

    // Lights
    DirectionalLight directionalLight;
    PointLight pointLights[4] = {
        PointLight{.position = Vector3(0.7f, 0.2f, 2.0f)},
        PointLight{.position = Vector3(2.3f, -3.3f, -4.0f)},
        PointLight{.position = Vector3(-4.0f, 2.0f, -12.0f)},
        PointLight{.position = Vector3(0.0f, 0.0f, -3.0f)}
    };
    SpotLight spotLight;

  public:
    Renderer3D();

    ~Renderer3D();

    void Render();
};

#endif //RENDERER3D_H
