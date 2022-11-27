#include "MovementSystem.h"
#include "Components/MovementComponent.h"
#include "Components/TransformComponent.h"
#include "Entity/Entity.h"
#include "Helper/Application.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

UMovementSystem::UMovementSystem() {
    RequiredComponentClasses.push_back(EComponentClass::UMovementComponent);
    RequiredComponentClasses.push_back(EComponentClass::UTransformComponent);
}

void UMovementSystem::Update(float DeltaTime, UEntity* Entity) {
    if (!Entity) {
        assert(false);
        return;
    }

    UMovementComponent* MovementComponent =
        Entity->GetComponentOfClass<UMovementComponent>();

    if (!MovementComponent) {
        assert(false);
        return;
    }

    UTransformComponent* TransformComponent =
        Entity->GetComponentOfClass<UTransformComponent>();

    if (!TransformComponent) {
        assert(false);
        return;
    }

    UpdateTransformComponent(DeltaTime, MovementComponent, TransformComponent);
}

void UMovementSystem::UpdateTransformComponent(
    float DeltaTime,
    const UMovementComponent* MovementComponent,
    UTransformComponent* TransformComponent) {
    if (!TransformComponent || !MovementComponent) {
        assert(false);
        return;
    }

    const glm::vec3 LocationDelta =
        MovementComponent->GetVelocityScaled() * DeltaTime;

    if (glm::dot(LocationDelta, LocationDelta) < 0.000001)
        return;

    const glm::vec3 PreviousPosition = TransformComponent->GetLocation();

    TransformComponent->SetPosition(PreviousPosition + LocationDelta);
}
