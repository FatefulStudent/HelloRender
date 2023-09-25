#include "StaticCameraSystem.h"
#include "Components/CameraComponent.h"
#include "Components/TransformComponent.h"
#include "Entity/Entity.h"
#include "Helper/Application.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

namespace {
constexpr glm::vec3 upVector{0.0f, 1.0f, 0.0f};
}

StaticCameraSystem::StaticCameraSystem() {
    requiredComponentClasses.push_back(EComponentClass::cameraComponent);
    requiredComponentClasses.push_back(EComponentClass::transformComponent);
}

void StaticCameraSystem::Initialize(Entity* entity) {
    if (!entity) {
        assert(false);
        return;
    }

    CameraComponent* cameraComponent =
        entity->GetComponentOfClass<CameraComponent>();

    if (!cameraComponent) {
        assert(false);
        return;
    }

    TransformComponent* transformComponent =
        entity->GetComponentOfClass<TransformComponent>();

    if (!transformComponent) {
        assert(false);
        return;
    }
    InitializeCameraComponent(cameraComponent, transformComponent);
}

void StaticCameraSystem::InitializeCameraComponent(
    CameraComponent* cameraComponent,
    TransformComponent* transformComponent) {
    if (!cameraComponent) {
        assert(false);
        return;
    }

    if (!transformComponent) {
        assert(false);
        return;
    }

    const glm::vec3& CameraRotation = transformComponent->GetRotation();
    const float Yaw = CameraRotation.x;
    const float Pitch = CameraRotation.y;
    // NB: we ignore Roll for camera

    const glm::vec3& CameraPosition = transformComponent->GetLocation();

    glm::vec3 Direction{};
    Direction.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Direction.y = sin(glm::radians(Pitch));
    Direction.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));

    glm::vec3 CameraTarget = CameraPosition + Direction;

    cameraComponent->view =
        glm::lookAt(CameraPosition, CameraTarget, upVector);

    cameraComponent->projection =
        glm::ortho(Application::GetLeftBorder(), Application::GetRightBorder(),
                   Application::GetBottomBorder(), Application::GetUpBorder());

    /*CameraComponent->Projection = glm::perspective(
        glm::radians(CameraComponent->FOV), CameraComponent->AspectRatio,
        CameraComponent->MinDistance, CameraComponent->MaxDistance);*/
}

void StaticCameraSystem::Update(double deltaTime, Entity* entity) {
    if (!entity) {
        assert(false);
        return;
    }

    CameraComponent* cameraComponent =
        entity->GetComponentOfClass<CameraComponent>();

    if (!cameraComponent) {
        assert(false);
        return;
    }
}

void StaticCameraSystem::UpdateCameraComponent(
    CameraComponent* cameraComponent) {
    if (!cameraComponent) {
        assert(false);
        return;
    }
}

void StaticCameraSystem::Finalize(Entity* entity) {
    if (!entity) {
        assert(false);
        return;
    }

    CameraComponent* cameraComponent =
        entity->GetComponentOfClass<CameraComponent>();

    if (!cameraComponent) {
        assert(false);
        return;
    }
    FinalizeCameraComponent(cameraComponent);
}

void StaticCameraSystem::FinalizeCameraComponent(
    CameraComponent* cameraComponent) {
    if (!cameraComponent) {
        assert(false);
        return;
    }

    // TODO: some kind of clearing up?
}
