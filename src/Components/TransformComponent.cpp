#include "TransformComponent.h"

#include <glm/gtc/matrix_transform.hpp>

UTransformComponent::UTransformComponent(const glm::vec3& InPosition,
                                         const glm::vec3& InRotation,
                                         const glm::vec3& InScale)
    : UComponent(std::string("TransformComponent")),
      Position(InPosition),
      Rotation(InRotation),
      Scale(InScale) {
    ComponentClass = EComponentClass::UTransformComponent;
}

// TODO: move it to cache?
glm::mat4 UTransformComponent::ConstructTransformMatrix() const {
    glm::mat4 TransformMatrix(1.0f);

    {
        TransformMatrix = glm::translate(TransformMatrix, glm::vec3(Position));

        // TODO: find a way to do it in single operation using quat
        // pitch
        TransformMatrix =
            glm::rotate(TransformMatrix, glm::radians(Rotation.z),
                        glm::vec3(1.0f, 0.f, 0.0f));

        // yaw
        TransformMatrix =
            glm::rotate(TransformMatrix, glm::radians(Rotation.x),
                        glm::vec3(0.0f, 1.f, 0.0f));

        // roll
        TransformMatrix =
            glm::rotate(TransformMatrix, glm::radians(Rotation.y),
                        glm::vec3(0.0f, 0.f, 1.0f));

        TransformMatrix = glm::scale(TransformMatrix, Scale);
    };
    return TransformMatrix;
}
