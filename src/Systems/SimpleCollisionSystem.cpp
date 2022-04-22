#include "SimpleCollisionSystem.h"

#include "Components/MovementComponent.h"
#include "Components/SimpleCollisionComponent.h"
#include "Components/TransformComponent.h"
#include "Entity/Entity.h"
#include "Helper/Application.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

USimpleCollisionSystem::USimpleCollisionSystem() {
    RequiredComponentClasses.push_back(
        EComponentClass::USimpleCollisionComponent);
    RequiredComponentClasses.push_back(EComponentClass::UMovementComponent);
}

void USimpleCollisionSystem::Update(float DeltaTime, UEntity* Entity) {
    if (!Entity) {
        assert(false);
        return;
    }

    USimpleCollisionComponent* SimpleCollisionComponent =
        Entity->GetComponentOfClass<USimpleCollisionComponent>();

    if (!SimpleCollisionComponent) {
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

    CheckBorders(SimpleCollisionComponent, MovementComponent,
                 TransformComponent);
}

void USimpleCollisionSystem::CheckBorders(
    const USimpleCollisionComponent* CollisionComponent,
    UMovementComponent* MovementComponent,
    const UTransformComponent* TransformComponent) {
    if (!CollisionComponent || !MovementComponent) {
        assert(false);
        return;
    }

    glm::vec3& VelocityDir = MovementComponent->VelocityDir;
    const glm::vec3& Position = TransformComponent->Position;

    const float LeftSideOfCollision =
        Position.x + CollisionComponent->GetLeftBorderRelativeOffset();
    const float RightSideOfCollision =
        Position.x + CollisionComponent->GetRightBorderRelativeOffset();
    const float UpSideOfCollision =
        Position.y + CollisionComponent->GetUpBorderRelativeOffset();
    const float BottomSideOfCollision =
        Position.y + CollisionComponent->GetBottomBorderRelativeOffset();

    if (LeftSideOfCollision < Application::GetLeftBorder() ||
        RightSideOfCollision > Application::GetRightBorder())
        VelocityDir.x *= -1.0f;
    else if (BottomSideOfCollision < Application::GetBottomBorder() ||
             UpSideOfCollision > Application::GetUpBorder())
        VelocityDir.y *= -1.0f;
}
