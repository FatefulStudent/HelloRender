#ifndef MOVEMENT_COMPONENT_H
#define MOVEMENT_COMPONENT_H

#include "Component.h"

#include <glm/vec3.hpp>

class MovementComponent : public Component {
public:
    MovementComponent(const glm::vec3& inVelocityDir, float inSpeed);
    virtual ~MovementComponent() = default;

    glm::vec3 GetVelocityScaled() const;

    glm::vec3 velocityDir = glm::vec3(0);
    float speed = 0.0f;
};

#endif