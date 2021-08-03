#ifndef MATERIAL_COMPONENT_H
#define MATERIAL_COMPONENT_H

#include "../../../math/Vector3.h"
#include "../../../rendering/texture.h"

struct MaterialComponent {
    Vector3 ambient = Vector3(1.0f, 0.5f, 0.31f);
    Vector3 diffuse = Vector3(1.0f, 0.5f, 0.31f);
    Vector3 specular = Vector3(0.5f, 0.5f, 0.5f);
    float shininess = 64.0f;
    Texture *diffuseMap = nullptr;
    Texture *specularMap = nullptr;
};

#endif //MATERIAL_COMPONENT_H
