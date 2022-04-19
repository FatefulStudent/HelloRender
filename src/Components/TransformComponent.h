#ifndef TRANSFORM_COMPONENT_H
#define TRANSFORM_COMPONENT_H

#include "Component.h"

#include <glm/vec3.hpp>

class UTransformComponent : public UComponent {
public:
    UTransformComponent(const glm::vec3& InPosition,
                        const glm::vec3& InRotation,
                        const glm::vec3& InScale);
    virtual ~UTransformComponent(){}

    glm::vec3 Position{};
    // Pitch, Yaw, Roll
    glm::vec3 Rotation{};
    glm::vec3 Scale{};
};

#endif