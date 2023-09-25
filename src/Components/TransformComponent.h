#ifndef TRANSFORM_COMPONENT_H
#define TRANSFORM_COMPONENT_H

#include "Component.h"

#include <glm/matrix.hpp>
#include <glm/vec3.hpp>

struct FTransform {
    glm::vec3 location = glm::vec3(0.0f);
    glm::vec3 rotation = glm::vec3(0.0f);
    glm::vec3 scale = glm::vec3(1.0f);
};

class TransformComponent : public Component {
public:
    explicit TransformComponent(const FTransform& InTransform);
    virtual ~TransformComponent() = default;

    const FTransform& GetTransform() const;
    const glm::mat4& GetTransformMatrix();

    const glm::vec3& GetLocation() const;
    // Pitch, Yaw, Roll
    const glm::vec3& GetRotation() const;
    const glm::vec3& GetScale() const;

    void SetPosition(const glm::vec3& inLocation);
    void SetRotation(const glm::vec3& inRotation);
    void SetScale(const glm::vec3& inScale);

    void SetTransform(const FTransform& inTransform);

    void RecalculateTransformMatrix();
private:
    FTransform transform;
    glm::mat4 transformMatrix = glm::mat4(1.0f);
    bool bRecalculationNeeded = false;
};

#endif