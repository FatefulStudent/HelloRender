#include "TransformComponent.h"

#include <glm/gtc/matrix_transform.hpp>

#define SMALL_NUMBER 0.000001

// TODO: move to MathHelper
bool VectorsAreEqual(const glm::vec3& vec1,
                     const glm::vec3& vec2,
                     float tol = SMALL_NUMBER) {
    const glm::vec3 DiffVector = vec1 - vec2;
    const float LengthSquared = glm::dot(DiffVector, DiffVector);
    return LengthSquared < tol;
}

bool TransformsAreEqual(const FTransform& Transform1,
                        const FTransform& Transform2,
                        float tol = SMALL_NUMBER) {
    return VectorsAreEqual(Transform1.Location, Transform2.Location, tol) &&
           VectorsAreEqual(Transform1.Rotation, Transform2.Rotation, tol) &&
           VectorsAreEqual(Transform1.Scale, Transform2.Scale, tol);
}

UTransformComponent::UTransformComponent(const FTransform& InTransform)
    : UComponent(std::string("TransformComponent")), Transform(InTransform) {
    ComponentClass = EComponentClass::UTransformComponent;
    RecalculateTransformMatrix();
}

const FTransform& UTransformComponent::GetTransform() const {
    return Transform;
}

const glm::mat4& UTransformComponent::GetTransformMatrix() {
    if (bRecalculationNeeded)
        RecalculateTransformMatrix();

    return TransformMatrix;
}

const glm::vec3& UTransformComponent::GetLocation() const {
    return Transform.Location;
}

const glm::vec3& UTransformComponent::GetRotation() const {
    return Transform.Rotation;
}

const glm::vec3& UTransformComponent::GetScale() const {
    return Transform.Scale;
}

void UTransformComponent::SetPosition(const glm::vec3& InLocation) {
    if (VectorsAreEqual(InLocation, Transform.Location))
        return;

    Transform.Location = InLocation;
    bRecalculationNeeded = true;
//    RecalculateTransformMatrix();
}

void UTransformComponent::SetRotation(const glm::vec3& InRotation) {
    if (VectorsAreEqual(InRotation, Transform.Rotation))
        return;

    Transform.Rotation = InRotation;
    bRecalculationNeeded = true;
//    RecalculateTransformMatrix();
}

void UTransformComponent::SetScale(const glm::vec3& InScale) {
    if (VectorsAreEqual(InScale, Transform.Scale))
        return;

    Transform.Scale = InScale;
    bRecalculationNeeded = true;
//    RecalculateTransformMatrix();
}

void UTransformComponent::SetTransform(const FTransform& InTransform) {
    if (TransformsAreEqual(Transform, InTransform))
        return;

    Transform = InTransform;
    bRecalculationNeeded = true;
//    RecalculateTransformMatrix();
}

void UTransformComponent::RecalculateTransformMatrix() {
    if (!bRecalculationNeeded)
        return;
    bRecalculationNeeded = false;

    TransformMatrix = glm::mat4(1.0f);
    TransformMatrix =
        glm::translate(TransformMatrix, glm::vec3(Transform.Location));

    // TODO: find a way to do it in single operation using quat
    // pitch
    TransformMatrix =
        glm::rotate(TransformMatrix, glm::radians(Transform.Rotation.z),
                    glm::vec3(1.0f, 0.f, 0.0f));

    // yaw
    TransformMatrix =
        glm::rotate(TransformMatrix, glm::radians(Transform.Rotation.x),
                    glm::vec3(0.0f, 1.f, 0.0f));

    // roll
    TransformMatrix =
        glm::rotate(TransformMatrix, glm::radians(Transform.Rotation.y),
                    glm::vec3(0.0f, 0.f, 1.0f));

    TransformMatrix = glm::scale(TransformMatrix, Transform.Scale);
}
