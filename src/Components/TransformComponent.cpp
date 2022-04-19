#include "TransformComponent.h"


UTransformComponent::UTransformComponent(const glm::vec3& InPosition,
                                         const glm::vec3& InRotation,
                                         const glm::vec3& InScale)
    : Position(InPosition), Rotation(InRotation), Scale(InScale) {
    ComponentClass = EComponentClass::UTransformComponent;
}
