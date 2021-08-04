#include "renderer3d.h"

#include <SDL2/SDL.h>

#include "../project_properties.h"

Renderer3D::Renderer3D() {}

Renderer3D::~Renderer3D() {
    glDeleteVertexArrays(1, &cube.VAO);
    glDeleteVertexArrays(1, &light.VAO);
    glDeleteBuffers(1, &VBO);
}

void Renderer3D::Initialize() {
    glEnable(GL_DEPTH_TEST);
    // Buffer Setup
    // CUBE
    glGenVertexArrays(1, &cube.VAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(cube.VAO);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*) nullptr);
    glEnableVertexAttribArray(0);
    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*) (3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    // texture coords
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*) (6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    // LIGHT
    glGenVertexArrays(1, &light.VAO);
    glBindVertexArray(light.VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*) nullptr);
    glEnableVertexAttribArray(0);


    // Textures
    cube.material.diffuseMap = new Texture("assets/game_projects/3d_test/assets/container2.png",
                                           GL_REPEAT,
                                           GL_REPEAT,
                                           GL_LINEAR,
                                           GL_LINEAR);
    cube.material.specularMap = new Texture("assets/game_projects/3d_test/assets/container2_specular.png",
                                            GL_REPEAT,
                                            GL_REPEAT,
                                            GL_LINEAR,
                                            GL_LINEAR);

    // Shader
    cube.shader = Shader("src/core/rendering/shader/opengl_shaders/3d/cube.vs", "src/core/rendering/shader/opengl_shaders/3d/cube.fs");
    cube.shader.Use();
    cube.shader.SetInt("material.diffuse", 0);
    cube.shader.SetInt("material.specular", 1);

    light.shader = Shader("src/core/rendering/shader/opengl_shaders/3d/light.vs", "src/core/rendering/shader/opengl_shaders/3d/light.fs");
}

void Renderer3D::Render(CameraManager *cameraManager) {
    static ProjectProperties *projectProperties = ProjectProperties::GetInstance();
    const float aspectRatio = projectProperties->windowWidth / projectProperties->windowHeight;
    Camera3D camera = cameraManager->GetCurrentCamera3D();
    glm::mat4 projection = glm::perspective(glm::radians(camera.fieldOfView), aspectRatio, 0.1f, 100.0f);
    glm::mat4 view = CameraHandler::GetCameraViewMatrix(camera);

    if (!textureCubeDrawBatches.empty()) {
        RenderTextureCubes(projection, view, camera);
    }

    if (!pointLightDrawBatches.empty()) {
        RenderPointLights(projection, view);
    }

    textureCubeDrawBatches.clear();
    pointLightDrawBatches.clear();
}

void Renderer3D::RenderTextureCubes(glm::mat4 &projection, glm::mat4 &view, Camera3D &camera) {
    // world transformation
    glm::mat4 model = glm::mat4(1.0f);

    // CUBE
    cube.shader.Use();

    cube.shader.SetMatrix4Float("model", model);
    cube.shader.SetMatrix4Float("projection", projection);
    cube.shader.SetMatrix4Float("view", view);
    cube.shader.SetVec3Float("viewPos", camera.position);

    // LIGHTS
    // Directional Light
    cube.shader.SetVec3Float("dirLight.direction", directionalLight.direction);
    cube.shader.SetVec3Float("dirLight.ambient", directionalLight.ambient);
    cube.shader.SetVec3Float("dirLight.diffuse", directionalLight.diffuse);
    cube.shader.SetVec3Float("dirLight.specular", directionalLight.specular);

    // Point Lights
    for (unsigned int i = 0; i < pointLightDrawBatches.size(); i++) {
        const std::string &arrayPrefix = std::string("pointLights[" + std::to_string(i) + "]");
        cube.shader.SetVec3Float(arrayPrefix + ".position", pointLightDrawBatches[i].position);
        cube.shader.SetVec3Float(arrayPrefix + ".ambient", pointLightDrawBatches[i].ambient);
        cube.shader.SetVec3Float(arrayPrefix + ".diffuse", pointLightDrawBatches[i].diffuse);
        cube.shader.SetVec3Float(arrayPrefix + ".specular", pointLightDrawBatches[i].specular);
        cube.shader.SetFloat(arrayPrefix + ".constant", pointLightDrawBatches[i].constant);
        cube.shader.SetFloat(arrayPrefix + ".linear", pointLightDrawBatches[i].linear);
        cube.shader.SetFloat(arrayPrefix + ".quadratic", pointLightDrawBatches[i].quadratic);
    }

    // Spot Light
    cube.shader.SetVec3Float("spotLight.position", camera.position);
    cube.shader.SetVec3Float("spotLight.direction", camera.front);
    cube.shader.SetVec3Float("spotLight.ambient", spotLight.ambient);
    cube.shader.SetVec3Float("spotLight.diffuse", spotLight.diffuse);
    cube.shader.SetVec3Float("spotLight.specular", spotLight.specular);
    cube.shader.SetFloat("spotLight.constant", spotLight.constant);
    cube.shader.SetFloat("spotLight.linear", spotLight.linear);
    cube.shader.SetFloat("spotLight.quadratic", spotLight.quadratic);
    cube.shader.SetFloat("spotLight.cutOff", glm::cos(glm::radians(spotLight.cutoff)));
    cube.shader.SetFloat("spotLight.outerCutOff", glm::cos(glm::radians(spotLight.outerCutoff)));

    // Render
    glBindVertexArray(cube.VAO);
    for (TextureCubeDrawBatch &textureCubeDrawBatch : textureCubeDrawBatches) {
        // bind diffuse map
        glActiveTexture(GL_TEXTURE0);
        textureCubeDrawBatch.diffuseMap->Bind();
        // bind specular map
        glActiveTexture(GL_TEXTURE1);
        textureCubeDrawBatch.specularMap->Bind();

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, textureCubeDrawBatch.position.ToGLM());
        model = glm::rotate(model, glm::radians(textureCubeDrawBatch.rotationAngleInDegrees), textureCubeDrawBatch.rotationAxisInDegrees.ToGLM());
        cube.shader.SetMatrix4Float("model", model);

        cube.shader.SetFloat("material.shininess", textureCubeDrawBatch.shininess);

        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}

void Renderer3D::RenderPointLights(glm::mat4 &projection, glm::mat4 &view) {
    // POINT LIGHTS
    light.shader.Use();
    light.shader.SetMatrix4Float("projection", projection);
    light.shader.SetMatrix4Float("view", view);

    // Render
    glBindVertexArray(light.VAO);
    static bool testPoint = false;
    for (PointLightDrawBatch &pointLightDrawBatch : pointLightDrawBatches) {
        if (!testPoint) {
            Logger::GetInstance()->Debug("Point Light in loop!");
        }
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, pointLightDrawBatch.position.ToGLM());
        model = glm::scale(model, pointLightDrawBatch.scale.ToGLM());
        light.shader.SetMatrix4Float("model", model);

        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
    testPoint = true;
}

void Renderer3D::AddTextureCubeDrawBatch(TextureCubeDrawBatch textureCubeDrawBatch) {
    textureCubeDrawBatches.emplace_back(textureCubeDrawBatch);
}

void Renderer3D::AddPointLightDrawBatch(PointLightDrawBatch pointLightDrawBatch) {
    pointLightDrawBatches.emplace_back(pointLightDrawBatch);
}
