#include "shader.h"

static const std::string VERTEX = "VERTEX";
static const std::string FRAGMENT = "FRAGMENT";
static const std::string PROGRAM = "PROGRAM";

Logger *Shader::logger = Logger::GetInstance();

Shader::Shader() {}

Shader::Shader(const std::string &vertexPath, const std::string &fragmentPath) {
    Compile(GetOpenGLShaderSourceFromPaths(vertexPath, fragmentPath));
}

Shader::Shader(OpenGLShaderSourceCode openGlShaderSourceCode) {
    Compile(openGlShaderSourceCode);
}

Shader::~Shader() {}

OpenGLShaderSourceCode Shader::GetOpenGLShaderSourceFromPaths(const std::string &vertexPath, const std::string &fragmentPath) {
    std::ifstream vertexShaderFile;
    std::ifstream fragmentShaderFile;
    vertexShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fragmentShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    OpenGLShaderSourceCode openGlShaderSourceCode;
    try {
        // TODO: Validate file exists...
        vertexShaderFile.open(vertexPath.c_str());
        fragmentShaderFile.open(fragmentPath.c_str());
        std::stringstream vertexShaderStream, fragmentShaderStream;
        vertexShaderStream << vertexShaderFile.rdbuf();
        fragmentShaderStream << fragmentShaderFile.rdbuf();
        vertexShaderFile.close();
        fragmentShaderFile.close();
        openGlShaderSourceCode.vertex = vertexShaderStream.str();
        openGlShaderSourceCode.fragment = fragmentShaderStream.str();
    } catch(std::ifstream::failure& e) {
        logger->Error("Error reading shader files '" + vertexPath + "' and '" + fragmentPath + "'!");
    }
    return openGlShaderSourceCode;
}

void Shader::Compile(OpenGLShaderSourceCode openGlShaderSourceCode) {
    unsigned int vertex, fragment;
    const char *vertexSource = openGlShaderSourceCode.vertex.c_str();
    const char *fragmentSource = openGlShaderSourceCode.fragment.c_str();
    // vertex
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertexSource, nullptr);
    glCompileShader(vertex);
    CheckCompileErrors(vertex, VERTEX);
    // fragment
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragmentSource, nullptr);
    glCompileShader(fragment);
    CheckCompileErrors(fragment, FRAGMENT);
    // shader
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    CheckCompileErrors(ID, PROGRAM);
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::Use() {
    glUseProgram(ID);
}

void Shader::SetBool(const std::string &name, bool value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::SetInt(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::SetFloat(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::SetVec2Float(const std::string &name, float v1, float v2) const {
    glUniform2f(glGetUniformLocation(this->ID, name.c_str()), v1, v2);
}

void Shader::SetVec3Float(const std::string &name, float v1, float v2, float v3) const {
    glUniform3f(glGetUniformLocation(this->ID, name.c_str()), v1, v2, v3);
}

void Shader::SetVec3Float(const std::string &name, const glm::vec3 &value) const {
    glUniform3f(glGetUniformLocation(this->ID, name.c_str()), value.x, value.y, value.z);
}

void Shader::SetVec3Float(const std::string &name, const Color &value) const {
    glUniform3f(glGetUniformLocation(this->ID, name.c_str()), value.r, value.g, value.b);
}

void Shader::SetVec4Float(const std::string &name, float v1, float v2, float v3, float v4) const {
    glUniform4f(glGetUniformLocation(this->ID, name.c_str()), v1, v2, v3, v4);
}

void Shader::SetVec4Float(const std::string &name, const Color &value) const {
    glUniform4f(glGetUniformLocation(this->ID, name.c_str()), value.r, value.g, value.b, value.a);
}

void Shader::SetMatrix4Float(const std::string &name, const glm::mat4 &mat) const {
    glUniformMatrix4fv(glGetUniformLocation(this->ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
}

void Shader::SetMatrix4Float(const std::string &name, const Matrix4 &mat) const {
    glUniformMatrix4fv(glGetUniformLocation(this->ID, name.c_str()), 1, GL_FALSE, mat.members);
}

void Shader::CheckCompileErrors(unsigned int shader, const std::string &type) {
    int success;
    char infoLog[1024];
    if(type == PROGRAM) {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if(!success) {
            glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
            logger->Error("Shader type '" + type + "' linking failed!\n" + std::string(infoLog));
        }
    } else {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if(!success) {
            glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
            logger->Error("Shader type '" + type + "' compilation failed!\n" + std::string(infoLog));
        }
    }
}
