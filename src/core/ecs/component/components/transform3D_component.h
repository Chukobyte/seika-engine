#ifndef TRANSFORM3D_COMPONENT_H
#define TRANSFORM3D_COMPONENT_H

#include "../component.h"
#include "../../../math/vector3.h"

struct Transform3DComponent {
    Vector3 position = Vector3(0.0f);
    Vector3 scale = Vector3(1.0f);
    float rotationAngleInDegrees = 0;
    Vector3 rotationAxisInDegrees = Vector3(0.0f);
};

#endif //TRANSFORM3D_COMPONENT_H
