#ifndef OPENGL_SHADER_SOURCE_H
#define OPENGL_SHADER_SOURCE_H

#include <string>

struct OpenGLShaderSourceCode {
    std::string vertex;
    std::string fragment;
};

static const std::string &OPENGL_SHADER_SOURCE_VERTEX_FONT =
    "#version 330 core\n"
    "layout (location = 0) in vec4 vertex; // (pos, tex)\n"
    "\n"
    "out vec2 texCoords;\n"
    "\n"
    "uniform mat4 projection;\n"
    "\n"
    "void main() {\n"
    "    gl_Position = projection * vec4(vertex.xy, 0.0f, 1.0f);\n"
    "    texCoords = vertex.zw;\n"
    "}";

static const std::string &OPENGL_SHADER_SOURCE_FRAGMENT_FONT =
    "#version 330 core\n"
    "in vec2 texCoords;\n"
    "out vec4 color;\n"
    "\n"
    "uniform sampler2D textValue;\n"
    "uniform vec4 textColor;\n"
    "\n"
    "void main() {\n"
    "    vec4 sampled = vec4(1.0f, 1.0f, 1.0f, texture(textValue, texCoords).r);\n"
    "    color = textColor * sampled;\n"
    "}";

static const OpenGLShaderSourceCode OPENGL_SHADER_SOURCE_FONT = OpenGLShaderSourceCode{
    .vertex = OPENGL_SHADER_SOURCE_VERTEX_FONT,
    .fragment = OPENGL_SHADER_SOURCE_FRAGMENT_FONT
};

static const std::string &OPENGL_SHADER_SOURCE_VERTEX_POINT =
    "#version 330 core\n"
    "layout (location = 0) in vec4 vertex; // (pos, tex)\n"
    "\n"
    "out vec2 texCoords;\n"
    "\n"
    "uniform mat4 projection;\n"
    "\n"
    "void main() {\n"
    "    gl_Position = projection * vec4(vertex.xy, 0.0f, 1.0f);\n"
    "    texCoords = vertex.zw;\n"
    "}";

static const std::string &OPENGL_SHADER_SOURCE_FRAGMENT_POINT =
    "#version 330 core\n"
    "in vec2 texCoords;\n"
    "out vec4 color;\n"
    "\n"
    "uniform sampler2D textValue;\n"
    "uniform vec4 textColor;\n"
    "\n"
    "void main() {\n"
    "    vec4 sampled = vec4(1.0f, 1.0f, 1.0f, texture(textValue, texCoords).r);\n"
    "    color = textColor * sampled;\n"
    "}";

static const OpenGLShaderSourceCode OPENGL_SHADER_SOURCE_POINT = OpenGLShaderSourceCode{
    .vertex = OPENGL_SHADER_SOURCE_VERTEX_POINT,
    .fragment = OPENGL_SHADER_SOURCE_FRAGMENT_POINT
};

static const std::string &OPENGL_SHADER_SOURCE_VERTEX_SPRITE =
    "#version 330 core\n"
    "\n"
    "layout (location = 0) in vec4 vertex;\n"
    "\n"
    "out vec2 texCoord;\n"
    "\n"
    "uniform mat4 projection;\n"
    "uniform mat4 model;\n"
    "\n"
    "void main() {\n"
    "    texCoord = vertex.zw;\n"
    "    gl_Position = projection * model * vec4(vertex.xy, 0.0f, 1.0f);\n"
    "}";

static const std::string &OPENGL_SHADER_SOURCE_FRAGMENT_SPRITE =
    "#version 330 core\n"
    "\n"
    "in vec2 texCoord;\n"
    "out vec4 color;\n"
    "\n"
    "uniform sampler2D sprite;\n"
    "uniform vec4 spriteColor;\n"
    "\n"
    "void main() {\n"
    "    color = spriteColor * texture(sprite, texCoord);\n"
    "}";

static const OpenGLShaderSourceCode OPENGL_SHADER_SOURCE_SPRITE = OpenGLShaderSourceCode{
    .vertex = OPENGL_SHADER_SOURCE_VERTEX_SPRITE,
    .fragment = OPENGL_SHADER_SOURCE_FRAGMENT_SPRITE
};

#endif //OPENGL_SHADER_SOURCE_H
