#ifndef RENDERER3D_H
#define RENDERER3D_H

#include <vector>

#include <glad/glad.h>

#include "texture.h"
#include "shader/shader.h"
#include "../math/vector3.h"
#include "../camera/camera_manager.h"

struct TextureCubeDrawBatch {
    Vector3 position = Vector3(0.0f);
    Vector3 scale = Vector3(1.0f);
    float rotationAngleInDegrees = 0;
    Vector3 rotationAxisInDegrees = Vector3(0.0f);
    Texture *diffuseMap = nullptr;
    Texture *specularMap = nullptr;
    float shininess = 0.0f;
};

struct DirectionalLightDrawBatch {
    Vector3 direction = Vector3(-0.2f, -1.0f, -0.3f);
    Vector3 ambient = Vector3(0.05f, 0.05f, 0.05f);
    Vector3 diffuse = Vector3(0.4f, 0.4f, 0.4f);
    Vector3 specular = Vector3(0.5f, 0.5f, 0.5f);
};

struct PointLightDrawBatch {
    Vector3 position = Vector3(0.0f);
    Vector3 scale = Vector3(0.2f);
    Vector3 ambient = Vector3(0.05f);
    Vector3 diffuse = Vector3(0.8f);
    Vector3 specular = Vector3(1.0f);
    float linear = 0.09f;
    float quadratic = 0.032f;
    const float constant = 1.0f;
};

struct SpotLightDrawBatch {
    bool isAttachedToCamera = false;
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
    EntityMaterial material = EntityMaterial{
        .ambient = Vector3(1.0f, 0.5f, 0.31f),
        .diffuse = Vector3(1.0f, 0.5f, 0.31f),
        .specular = Vector3(0.5f, 0.5f, 0.5f),
        .shininess = 32.0f
    };
};

struct DirectionalLight {
    Vector3 direction = Vector3(-0.2f, -1.0f, -0.3f);
    Vector3 ambient = Vector3(0.05f, 0.05f, 0.05f);
    Vector3 diffuse = Vector3(0.4f, 0.4f, 0.4f);
    Vector3 specular = Vector3(0.5f, 0.5f, 0.5f);
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
    bool initialized = false;
    GLuint VBO;
    LightEntity light;
    CubeEntity cube;

    // [0 - 2] = position, [3 - 5] = normals, [6 - 7] = texture coordinates
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

    std::vector<TextureCubeDrawBatch> textureCubeDrawBatches;
    std::vector<PointLightDrawBatch> pointLightDrawBatches;
    std::vector<SpotLightDrawBatch> spotLightDrawBatches;

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

    // Lights
    DirectionalLight directionalLight;
    SpotLight spotLight;

    void RenderTextureCubes(glm::mat4 &projection, glm::mat4 &view, Camera3D &camera);

    void RenderPointLights(glm::mat4 &projection, glm::mat4 &view);

  public:
    Renderer3D();

    ~Renderer3D();

    void Initialize();

    void Render(CameraManager *cameraManager);

    void AddTextureCubeDrawBatch(TextureCubeDrawBatch textureCubeDrawBatch);

    // TODO: Clean up, for now can only have one directional light
    void AddDirectionalLightDrawBatch(DirectionalLightDrawBatch directionalLightDrawBatch);

    void AddPointLightDrawBatch(PointLightDrawBatch pointLightDrawBatch);

    void AddSpotLightDrawBatch(SpotLightDrawBatch spotLightDrawBatch);

    void BatchDrawTextureCube();
};

#endif //RENDERER3D_H
