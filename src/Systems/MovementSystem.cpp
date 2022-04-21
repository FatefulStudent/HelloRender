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

    UpdateMovementComponent(MovementComponent, TransformComponent);
    UpdateTransformComponent(DeltaTime, MovementComponent, TransformComponent);
}

void UMovementSystem::UpdateMovementComponent(
    UMovementComponent* MovementComponent,
    const UTransformComponent* TransformComponent) {
    if (!TransformComponent || !MovementComponent) {
        assert(false);
        return;
    }

    glm::vec3& VelocityDir = MovementComponent->VelocityDir;
    const glm::vec3& Position = TransformComponent->Position;

    if (Position.x < Application::GetLeftBorder() ||
        Position.x > Application::GetRightBorder())
        VelocityDir.x *= -1.0f;
    else if (Position.y < Application::GetBottomBorder() ||
             Position.y > Application::GetUpBorder())
        VelocityDir.y *= -1.0f;
}

void UMovementSystem::UpdateTransformComponent(
    float DeltaTime,
    const UMovementComponent* MovementComponent,
    UTransformComponent* TransformComponent) {
    if (!TransformComponent || !MovementComponent) {
        assert(false);
        return;
    }

    TransformComponent->Position +=
        MovementComponent->GetVelocityScaled() * DeltaTime;
}
