#include "MovementSystem.h"
#include "Components/MovementComponent.h"
#include "Components/TransformComponent.h"
#include "Entity/Entity.h"
#include "Helper/Application.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

MovementSystem::MovementSystem() {
    requiredComponentClasses.push_back(EComponentClass::movementComponent);
    requiredComponentClasses.push_back(EComponentClass::transformComponent);
}

void MovementSystem::Update(double deltaTime, Entity* entity) {
    if (!entity) {
        assert(false);
        return;
    }

    MovementComponent* movementComponent =
        entity->GetComponentOfClass<MovementComponent>();

    if (!movementComponent) {
        assert(false);
        return;
    }

    TransformComponent* transformComponent =
        entity->GetComponentOfClass<TransformComponent>();

    if (!transformComponent) {
        assert(false);
        return;
    }

    UpdateTransformComponent(deltaTime, movementComponent, transformComponent);
}

void MovementSystem::UpdateTransformComponent(
    double deltaTime,
    const MovementComponent* movementComponent,
    TransformComponent* transformComponent) {
    if (!transformComponent || !movementComponent) {
        assert(false);
        return;
    }

    const glm::vec3 LocationDelta =
        movementComponent->GetVelocityScaled() * (float)deltaTime;

    if (glm::dot(LocationDelta, LocationDelta) < 0.000001)
        return;

    const glm::vec3 PreviousPosition = transformComponent->GetLocation();

    transformComponent->SetPosition(PreviousPosition + LocationDelta);
}
