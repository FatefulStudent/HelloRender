#ifndef CAMERA_COMPONENT_H
#define CAMERA_COMPONENT_H

#include "Component.h"

#include <glm/matrix.hpp>

class UCameraComponent : public UComponent {
public:
    UCameraComponent();
    virtual ~UCameraComponent() {}

    float FOV = 45.0f;
    float AspectRatio = 1.0f;
    float MinDistance = 0.1f;
    float MaxDistance = 500.f;
    glm::mat4 View{1.0f};
    glm::mat4 Projection{1.0f};
};

#endif