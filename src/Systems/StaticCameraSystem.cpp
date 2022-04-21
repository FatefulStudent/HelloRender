#include "StaticCameraSystem.h"
#include "Components/CameraComponent.h"
#include "Components/TransformComponent.h"
#include "Entity/Entity.h"
#include "Helper/Application.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

namespace {
constexpr glm::vec3 UpVector{0.0f, 1.0f, 0.0f};
}

UStaticCameraSystem::UStaticCameraSystem() {
    RequiredComponentClasses.push_back(EComponentClass::UCameraComponent);
    RequiredComponentClasses.push_back(EComponentClass::UTransformComponent);
}

void UStaticCameraSystem::Initialize(UEntity* Entity) {
    if (!Entity) {
        assert(false);
        return;
    }

    UCameraComponent* CameraComponent =
        Entity->GetComponentOfClass<UCameraComponent>();

    if (!CameraComponent) {
        assert(false);
        return;
    }

    UTransformComponent* TransformComponent =
        Entity->GetComponentOfClass<UTransformComponent>();

    if (!TransformComponent) {
        assert(false);
        return;
    }
    InitializeCameraComponent(CameraComponent, TransformComponent);
}

void UStaticCameraSystem::InitializeCameraComponent(
    UCameraComponent* CameraComponent,
    UTransformComponent* TransformComponent) {
    if (!CameraComponent) {
        assert(false);
        return;
    }

    if (!TransformComponent) {
        assert(false);
        return;
    }

    const glm::vec3& CameraRotation = TransformComponent->Rotation;
    const float Yaw = CameraRotation.x;
    const float Pitch = CameraRotation.y;
    // NB: we ignore Roll for camera

    const glm::vec3& CameraPosition = TransformComponent->Position;

    glm::vec3 Direction{};
    Direction.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Direction.y = sin(glm::radians(Pitch));
    Direction.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));

    glm::vec3 CameraTarget = CameraPosition + Direction;

    CameraComponent->View =
        glm::lookAt(CameraPosition, CameraTarget, UpVector);

    CameraComponent->Projection =
        glm::ortho(Application::GetLeftBorder(), Application::GetRightBorder(),
                   Application::GetBottomBorder(), Application::GetUpBorder());

    /*CameraComponent->Projection = glm::perspective(
        glm::radians(CameraComponent->FOV), CameraComponent->AspectRatio,
        CameraComponent->MinDistance, CameraComponent->MaxDistance);*/
}

void UStaticCameraSystem::Update(UEntity* Entity) {
    if (!Entity) {
        assert(false);
        return;
    }

    UCameraComponent* CameraComponent =
        Entity->GetComponentOfClass<UCameraComponent>();

    if (!CameraComponent) {
        assert(false);
        return;
    }
}

void UStaticCameraSystem::UpdateCameraComponent(
    UCameraComponent* CameraComponent) {
    if (!CameraComponent) {
        assert(false);
        return;
    }
}

void UStaticCameraSystem::Finalize(UEntity* Entity) {
    if (!Entity) {
        assert(false);
        return;
    }

    UCameraComponent* CameraComponent =
        Entity->GetComponentOfClass<UCameraComponent>();

    if (!CameraComponent) {
        assert(false);
        return;
    }
    FinalizeCameraComponent(CameraComponent);
}

void UStaticCameraSystem::FinalizeCameraComponent(
    UCameraComponent* CameraComponent) {
    if (!CameraComponent) {
        assert(false);
        return;
    }

    // TODO: some kind of clearing up?
}
