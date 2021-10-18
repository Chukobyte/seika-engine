#ifndef OPENGL_SHADER_SOURCE_H
#define OPENGL_SHADER_SOURCE_H

#include <string>

struct OpenGLShaderSourceCode {
    std::string vertex;
    std::string fragment;
};

// 2D
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

// 3D
static const std::string &OPENGL_SHADER_SOURCE_CUBE_VERTEX =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "layout (location = 1) in vec3 aNormal;\n"
    "layout (location = 2) in vec2 aTexCoords;\n"
    "\n"
    "out vec3 FragPos;\n"
    "out vec3 Normal;\n"
    "out vec2 TexCoords;\n"
    "\n"
    "uniform mat4 model;\n"
    "uniform mat4 view;\n"
    "uniform mat4 projection;\n"
    "\n"
    "void main() {\n"
    "    FragPos = vec3(model * vec4(aPos, 1.0));\n"
    "    Normal = mat3(transpose(inverse(model))) * aNormal;\n"
    "    TexCoords = aTexCoords;\n"
    "\n"
    "    gl_Position = projection * view * vec4(FragPos, 1.0);\n"
    "}\n";

static const std::string &OPENGL_SHADER_SOURCE_CUBE_FRAGMENT =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "\n"
    "struct Material {\n"
    "    sampler2D diffuse;\n"
    "    sampler2D specular;\n"
    "    float shininess;\n"
    "};\n"
    "\n"
    "struct DirLight {\n"
    "    vec3 direction;\n"
    "\n"
    "    vec3 ambient;\n"
    "    vec3 diffuse;\n"
    "    vec3 specular;\n"
    "};\n"
    "\n"
    "struct PointLight {\n"
    "    vec3 position;\n"
    "\n"
    "    float constant;\n"
    "    float linear;\n"
    "    float quadratic;\n"
    "\n"
    "    vec3 ambient;\n"
    "    vec3 diffuse;\n"
    "    vec3 specular;\n"
    "};\n"
    "\n"
    "struct SpotLight {\n"
    "    vec3 position;\n"
    "    vec3 direction;\n"
    "    float cutOff;\n"
    "    float outerCutOff;\n"
    "\n"
    "    float constant;\n"
    "    float linear;\n"
    "    float quadratic;\n"
    "\n"
    "    vec3 ambient;\n"
    "    vec3 diffuse;\n"
    "    vec3 specular;\n"
    "};\n"
    "\n"
    "#define MAX_DIRECTIONAL_LIGHTS 20\n"
    "#define MAX_POINT_LIGHTS 20\n"
    "#define MAX_SPOT_LIGHTS 20\n"
    "\n"
    "in vec3 FragPos;\n"
    "in vec3 Normal;\n"
    "in vec2 TexCoords;\n"
    "\n"
    "uniform vec3 viewPos;\n"
    "uniform DirLight directionalLights[MAX_DIRECTIONAL_LIGHTS];\n"
    "uniform int numberOfDirectionalLights;\n"
    "uniform PointLight pointLights[MAX_POINT_LIGHTS];\n"
    "uniform int numberOfPointLights;\n"
    "uniform SpotLight spotLights[MAX_SPOT_LIGHTS];\n"
    "uniform int numberOfSpotLights;\n"
    "uniform Material material;\n"
    "\n"
    "// function prototypes\n"
    "vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);\n"
    "vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);\n"
    "vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);\n"
    "\n"
    "void main() {\n"
    "    // properties\n"
    "    vec3 norm = normalize(Normal);\n"
    "    vec3 viewDir = normalize(viewPos - FragPos);\n"
    "\n"
    "    // == =====================================================\n"
    "    // Our lighting is set up in 3 phases: directional, point lights and an optional flashlight\n"
    "    // For each phase, a calculate function is defined that calculates the corresponding color\n"
    "    // per lamp. In the main() function we take all the calculated colors and sum them up for\n"
    "    // this fragment's final color.\n"
    "    // == =====================================================\n"
    "    vec3 result = vec3(0.0f);\n"
    "    // phase 1: directional lighting\n"
    "    for(int i = 0; i < numberOfDirectionalLights; i++) {\n"
    "        result += CalcDirLight(directionalLights[i], norm, viewDir);\n"
    "    }\n"
    "    // phase 2: point lights\n"
    "    for(int i = 0; i < numberOfPointLights; i++) {\n"
    "        result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);\n"
    "    }\n"
    "    // phase 3: spot light\n"
    "    for(int i = 0; i < numberOfSpotLights; i++) {\n"
    "        result += CalcSpotLight(spotLights[i], norm, FragPos, viewDir);\n"
    "    }\n"
    "\n"
    "    FragColor = vec4(result, 1.0);\n"
    "}\n"
    "\n"
    "// calculates the color when using a directional light.\n"
    "vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir) {\n"
    "    vec3 lightDir = normalize(-light.direction);\n"
    "    // diffuse shading\n"
    "    float diff = max(dot(normal, lightDir), 0.0);\n"
    "    // specular shading\n"
    "    vec3 reflectDir = reflect(-lightDir, normal);\n"
    "    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);\n"
    "    // combine results\n"
    "    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));\n"
    "    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));\n"
    "    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));\n"
    "    return (ambient + diffuse + specular);\n"
    "}\n"
    "\n"
    "// calculates the color when using a point light.\n"
    "vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {\n"
    "    vec3 lightDir = normalize(light.position - fragPos);\n"
    "    // diffuse shading\n"
    "    float diff = max(dot(normal, lightDir), 0.0);\n"
    "    // specular shading\n"
    "    vec3 reflectDir = reflect(-lightDir, normal);\n"
    "    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);\n"
    "    // attenuation\n"
    "    float distance = length(light.position - fragPos);\n"
    "    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));\n"
    "    // combine results\n"
    "    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));\n"
    "    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));\n"
    "    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));\n"
    "    ambient *= attenuation;\n"
    "    diffuse *= attenuation;\n"
    "    specular *= attenuation;\n"
    "    return (ambient + diffuse + specular);\n"
    "}\n"
    "\n"
    "// calculates the color when using a spot light.\n"
    "vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {\n"
    "    vec3 lightDir = normalize(light.position - fragPos);\n"
    "    // diffuse shading\n"
    "    float diff = max(dot(normal, lightDir), 0.0);\n"
    "    // specular shading\n"
    "    vec3 reflectDir = reflect(-lightDir, normal);\n"
    "    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);\n"
    "    // attenuation\n"
    "    float distance = length(light.position - fragPos);\n"
    "    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));\n"
    "    // spotlight intensity\n"
    "    float theta = dot(lightDir, normalize(-light.direction));\n"
    "    float epsilon = light.cutOff - light.outerCutOff;\n"
    "    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);\n"
    "    // combine results\n"
    "    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));\n"
    "    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));\n"
    "    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));\n"
    "    ambient *= attenuation * intensity;\n"
    "    diffuse *= attenuation * intensity;\n"
    "    specular *= attenuation * intensity;\n"
    "    return (ambient + diffuse + specular);\n"
    "}\n";

static const OpenGLShaderSourceCode OPENGL_SHADER_SOURCE_CUBE = OpenGLShaderSourceCode{
    .vertex = OPENGL_SHADER_SOURCE_CUBE_VERTEX,
    .fragment = OPENGL_SHADER_SOURCE_CUBE_FRAGMENT
};

static const std::string &OPENGL_SHADER_SOURCE_LIGHT_VERTEX =
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "\n"
    "uniform mat4 model;\n"
    "uniform mat4 view;\n"
    "uniform mat4 projection;\n"
    "\n"
    "void main() {\n"
    "    gl_Position = projection * view * model * vec4(aPos, 1.0);\n"
    "}\n";

static const std::string &OPENGL_SHADER_SOURCE_LIGHT_FRAGMENT =
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "\n"
    "void main() {\n"
    "    FragColor = vec4(1.0); // set alle 4 vector values to 1.0\n"
    "}\n";

static const OpenGLShaderSourceCode OPENGL_SHADER_SOURCE_LIGHT = OpenGLShaderSourceCode{
    .vertex = OPENGL_SHADER_SOURCE_LIGHT_VERTEX,
    .fragment = OPENGL_SHADER_SOURCE_LIGHT_FRAGMENT
};

#endif //OPENGL_SHADER_SOURCE_H
