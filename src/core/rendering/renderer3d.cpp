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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*) nullptr);
    glEnableVertexAttribArray(0);

    // LIGHT
    glGenVertexArrays(1, &light.VAO);
    glBindVertexArray(light.VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*) nullptr);
    glEnableVertexAttribArray(0);

    // Shader
    cube.shader = Shader("src/core/rendering/shader/opengl_shaders/3d/cube.vs", "src/core/rendering/shader/opengl_shaders/3d/cube.fs");
    light.shader = Shader("src/core/rendering/shader/opengl_shaders/3d/light.vs", "src/core/rendering/shader/opengl_shaders/3d/light.fs");
}

Renderer3D::~Renderer3D() {
    glDeleteVertexArrays(1, &cube.VAO);
    glDeleteVertexArrays(1, &light.VAO);
    glDeleteBuffers(1, &VBO);
}

void Renderer3D::Render() {
    glm::mat4 projection = glm::perspective(glm::radians(fieldOfView), 800.0f / 600.0f, 0.1f, 100.0f);
    static CameraManager *cameraManager = GD::GetContainer()->cameraManager;
    Camera3D camera = cameraManager->GetCurrentCamera3D();
    glm::mat4 view = CameraHandler::GetCameraViewMatrix(camera);

    // world transformation
    glm::mat4 model = glm::mat4(1.0f);

    // CUBE
    cube.shader.Use();
    cube.shader.SetVec3Float("objectColor", Color(1.0f, 0.5f, 0.31f));
    cube.shader.SetVec3Float("lightColor", Color(1.0f, 1.0f, 1.0f));
    cube.shader.SetMatrix4Float("projection", projection);
    cube.shader.SetMatrix4Float("view", view);
    cube.shader.SetMatrix4Float("model", model);

    // Render
    glBindVertexArray(cube.VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);

    // LIGHT
    model = glm::mat4(1.0f);
    model = glm::translate(model, light.position.ToGLM());
    model = glm::scale(model, glm::vec3(light.scale));
    light.shader.Use();
    light.shader.SetMatrix4Float("projection", projection);
    light.shader.SetMatrix4Float("view", view);
    light.shader.SetMatrix4Float("model", model);

    // Render
    glBindVertexArray(light.VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}
