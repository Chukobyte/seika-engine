#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "../../math/matrices.h"

#include "opengl_shaders/opengl_shader_source.h"
#include "../../color.h"

#include "../../utils/logger.h"

class Shader {
  private:
    static Logger *logger;
    void CheckCompileErrors(unsigned int shader, const std::string &type);
  public:

    unsigned int ID;

    Shader();

    Shader(const std::string &vertexPath, const std::string &fragmentPath);

    Shader(OpenGLShaderSourceCode openGlShaderSourceCode);

    ~Shader();

    OpenGLShaderSourceCode GetOpenGLShaderSourceFromPaths(const std::string &vertexPath, const std::string &fragmentPath);

    void Compile(OpenGLShaderSourceCode openGlShaderSourceCode);

    void Use();

    void SetBool(const std::string &name, bool value) const;

    void SetInt(const std::string &name, int value) const;

    void SetFloat(const std::string &name, float value) const;

    void SetVec2Float(const std::string &name, float v1, float v2) const;

    void SetVec3Float(const std::string &name, const glm::vec3 &value) const;

    void SetVec3Float(const std::string &name, const Color &color) const;

    void SetVec3Float(const std::string &name, float v1, float v2, float v3) const;

    void SetVec4Float(const std::string &name, float v1, float v2, float v3, float v4) const;

    void SetVec4Float(const std::string &name, const Color &value) const;

    void SetMatrix4Float(const std::string &name, const glm::mat4 &mat) const;

    void SetMatrix4Float(const std::string &name, const Matrix4 &mat) const;
};

#endif //SHADER_H
