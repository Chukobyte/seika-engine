#include "renderer3d.h"

#include <SDL2/SDL.h>

#include "../global_dependencies.h"

Renderer3D::Renderer3D() {
    glEnable(GL_DEPTH_TEST);
    // Buffer Setup
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*) nullptr);
    glEnableVertexAttribArray(0);
    // texture coords attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*) (3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    // Shader
    shader = Shader("src/core/rendering/shader/opengl_shaders/3d.vs", "src/core/rendering/shader/opengl_shaders/3d.fs");
    shader.Use();
    shader.SetInt("texture1", 0);
    shader.SetInt("texture2", 1);

    // Load Textures
    containerTexture = new Texture("assets/game_projects/3d_test/assets/container.jpg",
                                   GL_REPEAT,
                                   GL_REPEAT,
                                   GL_LINEAR,
                                   GL_LINEAR,
                                   GL_RGB);

    awesomeFaceTexture = new Texture("assets/game_projects/3d_test/assets/awesomeface.png",
                                     GL_REPEAT,
                                     GL_REPEAT,
                                     GL_LINEAR,
                                     GL_LINEAR,
                                     GL_RGBA);

}

Renderer3D::~Renderer3D() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Renderer3D::Render() {
    shader.Use();

    glActiveTexture(GL_TEXTURE0);
    containerTexture->Bind();
    glActiveTexture(GL_TEXTURE1);
    awesomeFaceTexture->Bind();

    // pass projection matrix to shader (note that in this case it could change every frame)
    glm::mat4 projection = glm::perspective(glm::radians(fieldOfView), 800.0f / 600.0f, 0.1f, 100.0f);
    shader.SetMatrix4Float("projection", projection);

    // camera/view transformation
    static CameraManager *cameraManager = GD::GetContainer()->cameraManager;
    Camera3D camera = cameraManager->GetCurrentCamera3D();
    glm::mat4 view = glm::lookAt(camera.position.ToGLM(),
                                 camera.position.ToGLM() + camera.front.ToGLM(),
                                 camera.up.ToGLM());
    shader.SetMatrix4Float("view", view);

    // render boxes
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    for (unsigned int i = 0; i < 10; i++) {
        // calculate the model matrix for each object and pass it to shader before drawing
        glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        model = glm::translate(model, cubePositions[i].ToGLM());
        float angle = 20.0f * i + (SDL_GetTicks() / 5.0f);
        model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
        shader.SetMatrix4Float("model", model);

        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}
