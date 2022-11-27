#ifndef TRANSFORM_COMPONENT_H
#define TRANSFORM_COMPONENT_H

#include "Component.h"

#include <glm/matrix.hpp>
#include <glm/vec3.hpp>

struct FTransform {
    glm::vec3 Location = glm::vec3(0.0f);
    glm::vec3 Rotation = glm::vec3(0.0f);
    glm::vec3 Scale = glm::vec3(1.0f);
};

class UTransformComponent : public UComponent {
public:
    explicit UTransformComponent(const FTransform& InTransform);
    virtual ~UTransformComponent() = default;

    const FTransform& GetTransform() const;
    const glm::mat4& GetTransformMatrix();

    const glm::vec3& GetLocation() const;
    // Pitch, Yaw, Roll
    const glm::vec3& GetRotation() const;
    const glm::vec3& GetScale() const;

    void SetPosition(const glm::vec3& InLocation);
    void SetRotation(const glm::vec3& InRotation);
    void SetScale(const glm::vec3& InScale);

    void SetTransform(const FTransform& InTransform);

    void RecalculateTransformMatrix();
private:
    FTransform Transform;
    glm::mat4 TransformMatrix = glm::mat4(1.0f);
    bool bRecalculationNeeded = false;
};

#endif