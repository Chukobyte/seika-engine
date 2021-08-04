#ifndef LIGHT3D_COMPONENT_H
#define LIGHT3D_COMPONENT_H

#include "../../../math/vector3.h"

struct DirectionalLightComponent {
    Vector3 direction = Vector3(-0.2f, -1.0f, -0.3f);
};

struct PointLightComponent {
    float linear = 0.09f;
    float quadratic = 0.032f;
    float constant = 1.0f;
};

struct SpotLightComponent {
    Vector3 direction = Vector3(0.0f);
    bool isAttachedToCamera = false;
    float cutoffInDegrees = 12.5f;
    float outerCutoffInDegrees = 15.0f;
    float linear = 0.09f;
    float quadratic = 0.032f;
    float constant = 1.0f;
};

#endif //LIGHT3D_COMPONENT_H
