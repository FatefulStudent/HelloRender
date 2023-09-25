#ifndef CAMERA_COMPONENT_H
#define CAMERA_COMPONENT_H

#include "Component.h"

#include <glm/matrix.hpp>

class CameraComponent : public Component {
public:
    CameraComponent();
    virtual ~CameraComponent() = default;

    float fov = 45.0f;
    float minDistance = 0.1f;
    float maxDistance = 500.f;
    glm::mat4 view{1.0f};
    glm::mat4 projection{1.0f};
};

#endif