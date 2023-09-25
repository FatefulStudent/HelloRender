#include "SimpleCollisionSystem.h"

#include "Components/MovementComponent.h"
#include "Components/SimpleCollisionComponent.h"
#include "Components/TransformComponent.h"
#include "Entity/Entity.h"
#include "Helper/Application.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

SimpleCollisionSystem::SimpleCollisionSystem() {
    requiredComponentClasses.push_back(
        EComponentClass::simpleCollisionComponent);
    requiredComponentClasses.push_back(EComponentClass::movementComponent);
}

void SimpleCollisionSystem::Update(double DeltaTime, Entity* Entity) {
    if (!Entity) {
        assert(false);
        return;
    }

    SimpleCollisionComponent* simpleCollisionComponent =
        Entity->GetComponentOfClass<SimpleCollisionComponent>();

    if (!simpleCollisionComponent) {
        assert(false);
        return;
    }

    MovementComponent* movementComponent =
        Entity->GetComponentOfClass<MovementComponent>();

    if (!movementComponent) {
        assert(false);
        return;
    }

    TransformComponent* transformComponent =
        Entity->GetComponentOfClass<TransformComponent>();

    if (!transformComponent) {
        assert(false);
        return;
    }

    CheckBorders(simpleCollisionComponent, movementComponent,
                 transformComponent);
}

void SimpleCollisionSystem::CheckBorders(
    const SimpleCollisionComponent* collisionComponent,
    MovementComponent* movementComponent,
    const TransformComponent* transformComponent) {
    if (!collisionComponent || !movementComponent) {
        assert(false);
        return;
    }

    glm::vec3& velocityDir = movementComponent->velocityDir;
    const glm::vec3& location = transformComponent->GetLocation();

    const float leftSideOfCollision =
        location.x + collisionComponent->GetLeftBorderRelativeOffset();
    const float rightSideOfCollision =
        location.x + collisionComponent->GetRightBorderRelativeOffset();
    const float upSideOfCollision =
        location.y + collisionComponent->GetUpBorderRelativeOffset();
    const float bottomSideOfCollision =
        location.y + collisionComponent->GetBottomBorderRelativeOffset();

    if (leftSideOfCollision < Application::GetLeftBorder() ||
        rightSideOfCollision > Application::GetRightBorder())
        velocityDir.x *= -1.0f;
    else if (bottomSideOfCollision < Application::GetBottomBorder() ||
             upSideOfCollision > Application::GetUpBorder())
        velocityDir.y *= -1.0f;
}
