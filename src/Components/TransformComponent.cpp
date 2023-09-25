#include "TransformComponent.h"

#include <glm/gtc/matrix_transform.hpp>

#define SMALL_NUMBER 0.000001

// TODO: move to MathHelper
bool VectorsAreEqual(const glm::vec3& vec1,
                     const glm::vec3& vec2,
                     float tol = SMALL_NUMBER) {
    const glm::vec3 diffVector = vec1 - vec2;
    const float lengthSquared = glm::dot(diffVector, diffVector);
    return lengthSquared < tol;
}

bool TransformsAreEqual(const FTransform& transform1,
                        const FTransform& transform2,
                        float tol = SMALL_NUMBER) {
    return VectorsAreEqual(transform1.location, transform2.location, tol) &&
           VectorsAreEqual(transform1.rotation, transform2.rotation, tol) &&
           VectorsAreEqual(transform1.scale, transform2.scale, tol);
}

TransformComponent::TransformComponent(const FTransform& InTransform)
    : Component(std::string("TransformComponent")), transform(InTransform) {
    componentClass = EComponentClass::transformComponent;
    RecalculateTransformMatrix();
}

const FTransform& TransformComponent::GetTransform() const {
    return transform;
}

const glm::mat4& TransformComponent::GetTransformMatrix() {
    if (bRecalculationNeeded)
        RecalculateTransformMatrix();

    return transformMatrix;
}

const glm::vec3& TransformComponent::GetLocation() const {
    return transform.location;
}

const glm::vec3& TransformComponent::GetRotation() const {
    return transform.rotation;
}

const glm::vec3& TransformComponent::GetScale() const {
    return transform.scale;
}

void TransformComponent::SetPosition(const glm::vec3& inLocation) {
    if (VectorsAreEqual(inLocation, transform.location))
        return;

    transform.location = inLocation;
    bRecalculationNeeded = true;
//    RecalculateTransformMatrix();
}

void TransformComponent::SetRotation(const glm::vec3& inRotation) {
    if (VectorsAreEqual(inRotation, transform.rotation))
        return;

    transform.rotation = inRotation;
    bRecalculationNeeded = true;
//    RecalculateTransformMatrix();
}

void TransformComponent::SetScale(const glm::vec3& inScale) {
    if (VectorsAreEqual(inScale, transform.scale))
        return;

    transform.scale = inScale;
    bRecalculationNeeded = true;
//    RecalculateTransformMatrix();
}

void TransformComponent::SetTransform(const FTransform& inTransform) {
    if (TransformsAreEqual(transform, inTransform))
        return;

    transform = inTransform;
    bRecalculationNeeded = true;
//    RecalculateTransformMatrix();
}

void TransformComponent::RecalculateTransformMatrix() {
    if (!bRecalculationNeeded)
        return;
    bRecalculationNeeded = false;

    transformMatrix = glm::mat4(1.0f);
    transformMatrix =
        glm::translate(transformMatrix, glm::vec3(transform.location));

    // TODO: find a way to do it in single operation using quat
    // pitch
    transformMatrix =
        glm::rotate(transformMatrix, glm::radians(transform.rotation.z),
                    glm::vec3(1.0f, 0.f, 0.0f));

    // yaw
    transformMatrix =
        glm::rotate(transformMatrix, glm::radians(transform.rotation.x),
                    glm::vec3(0.0f, 1.f, 0.0f));

    // roll
    transformMatrix =
        glm::rotate(transformMatrix, glm::radians(transform.rotation.y),
                    glm::vec3(0.0f, 0.f, 1.0f));

    transformMatrix = glm::scale(transformMatrix, transform.scale);
}
