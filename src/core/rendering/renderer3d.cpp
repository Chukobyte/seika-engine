#include "renderer3d.h"

#include <SDL2/SDL.h>

#include "../global_dependencies.h"

Renderer3D::Renderer3D() {
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
    cube.material.diffuseMap = new Texture("assets/game_projects/3d_test/assets/container2.png");
    cube.material.specularMap = new Texture("assets/game_projects/3d_test/assets/container2_specular.png");

    // Shader
    cube.shader = Shader("src/core/rendering/shader/opengl_shaders/3d/cube.vs", "src/core/rendering/shader/opengl_shaders/3d/cube.fs");
    cube.shader.Use();
    cube.shader.SetInt("material.diffuse", 0);
    cube.shader.SetInt("material.specular", 1);

    light.shader = Shader("src/core/rendering/shader/opengl_shaders/3d/light.vs", "src/core/rendering/shader/opengl_shaders/3d/light.fs");
}

Renderer3D::~Renderer3D() {
    glDeleteVertexArrays(1, &cube.VAO);
    glDeleteVertexArrays(1, &light.VAO);
    glDeleteBuffers(1, &VBO);
}

void Renderer3D::Render() {
    static ProjectProperties *projectProperties = ProjectProperties::GetInstance();
    const float aspectRatio = projectProperties->windowWidth / projectProperties->windowHeight;
    glm::mat4 projection = glm::perspective(glm::radians(fieldOfView), aspectRatio, 0.1f, 100.0f);
    static CameraManager *cameraManager = GD::GetContainer()->cameraManager;
    Camera3D camera = cameraManager->GetCurrentCamera3D();
    glm::mat4 view = CameraHandler::GetCameraViewMatrix(camera);

    // world transformation
    glm::mat4 model = glm::mat4(1.0f);

    // Update light position
//    float time = SDL_GetTicks() / 256.0f;
//    light.position.x = sin(time) * 2.0f;
//    light.position.y = sin(time / 2.0f) * 1.0f;
//    light.position.z = cos(time) * 2.0f;

    light.material.diffuse = light.color * 0.5f;
    light.material.ambient = light.material.diffuse * 0.2f;

    // CUBE
    cube.shader.Use();

    cube.shader.SetMatrix4Float("model", model);
    cube.shader.SetMatrix4Float("projection", projection);
    cube.shader.SetMatrix4Float("view", view);
    cube.shader.SetVec3Float("viewPos", camera.position);
    cube.shader.SetFloat("material.shininess", cube.material.shininess);

    // LIGHTS
    // Directional Light
    cube.shader.SetVec3Float("dirLight.direction", directionalLight.direction);
    cube.shader.SetVec3Float("dirLight.ambient", directionalLight.ambient);
    cube.shader.SetVec3Float("dirLight.diffuse", directionalLight.diffuse);
    cube.shader.SetVec3Float("dirLight.specular", directionalLight.specular);

    // Point Lights
    for (unsigned int i = 0; i < sizeof(pointLights); i++) {
        const std::string &arrayPrefix = "pointLights[" + std::to_string(i) + "]";
        cube.shader.SetVec3Float(arrayPrefix + ".position", pointLights[i].position);
        cube.shader.SetVec3Float(arrayPrefix + ".ambient", pointLights[i].ambient);
        cube.shader.SetVec3Float(arrayPrefix + ".diffuse", pointLights[i].diffuse);
        cube.shader.SetVec3Float(arrayPrefix + ".specular", pointLights[i].specular);
        cube.shader.SetFloat(arrayPrefix + ".constant", pointLights[i].constant);
        cube.shader.SetFloat(arrayPrefix + ".linear", pointLights[i].linear);
        cube.shader.SetFloat(arrayPrefix + ".quadratic", pointLights[i].quadratic);
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

    // bind diffuse map
    glActiveTexture(GL_TEXTURE0);
    cube.material.diffuseMap->Bind();
    // bind specular map
    glActiveTexture(GL_TEXTURE1);
    cube.material.specularMap->Bind();

    // Render
    glBindVertexArray(cube.VAO);
    for (unsigned int i = 0; i < 10; i++) {
        // calculate the model matrix for each object and pass it to shader before drawing
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, cubePositions[i].ToGLM());
        float angle = 20.0f * i;
        model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
        cube.shader.SetMatrix4Float("model", model);

        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    // POINT LIGHTS
    light.shader.Use();
    light.shader.SetMatrix4Float("projection", projection);
    light.shader.SetMatrix4Float("view", view);

    // Render
    glBindVertexArray(light.VAO);
    for (unsigned int i = 0; i < sizeof(pointLights); i++) {
        model = glm::mat4(1.0f);
        model = glm::translate(model, pointLights[i].position.ToGLM());
        model = glm::scale(model, pointLights[i].scale.ToGLM());
        light.shader.SetMatrix4Float("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}
