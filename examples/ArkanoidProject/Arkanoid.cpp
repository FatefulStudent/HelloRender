#include "Arkanoid.h"

#include "Helper/Application.h"

#include "Components/Component.h"
#include "Components/ModelComponent.h"
#include "Components/ShaderComponent.h"
#include "Components/TransformComponent.h"
#include "Components/CameraComponent.h"
#include "Components/MovementComponent.h"
#include "Entity/Entity.h"
#include "World/World.h"

#include "Systems/RenderingSystem.h"
#include "Systems/ShaderSystem.h"
#include "Systems/System.h"
#include "Systems/StaticCameraSystem.h"
#include "Systems/MovementSystem.h"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <cassert>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>

namespace {

UEntity* CreatePlatform(UWorld* World) {
    if (!World) {
        assert(false);
        return nullptr;
    }

    const glm::vec3 Location{-5.0f, 0.0f, 0.0f};
    const glm::vec3 Rotation{-90.0f, 0.0f, 0.0f};
    const glm::vec3 Scale{1.f, 1.f, 1.f};
    const std::string ModelPath("res/platform/platform.obj");
    const std::string VertShaderPath("shaders/shaderForSun.vert");
    const std::string FragShaderPath("shaders/shaderForSun.frag");

    UEntity* Entity = World->CreateEntity();

    Entity->AddComponent<UShaderComponent>(VertShaderPath, 
                                           FragShaderPath);
    Entity->AddComponent<UModelComponent>(ModelPath);
    Entity->AddComponent<UTransformComponent>(Location, Rotation, Scale);

    return Entity;
}

UEntity* CreateEarth(UWorld* World) {
    if (!World) {
        assert(false);
        return nullptr;
    }

    const glm::vec3 Location{10.0f, 0.0f, 0.0f};
    const glm::vec3 Rotation{0.0f, 180.0f, 0.0f};
    const glm::vec3 Scale{1.f, 1.f, 1.f};

    const glm::vec3 VelocityDir{10.0f, 20.0f, 0.0f};
    const float Speed = 10.0f;
    const std::string ModelPath("res/earth/earth.obj");
    const std::string VertShaderPath("shaders/shaderForSun.vert");
    const std::string FragShaderPath("shaders/shaderForSun.frag");

    UEntity* Entity = World->CreateEntity();

    Entity->AddComponent<UShaderComponent>(VertShaderPath, FragShaderPath);
    Entity->AddComponent<UModelComponent>(ModelPath);
    Entity->AddComponent<UTransformComponent>(Location, Rotation, Scale);
    Entity->AddComponent<UMovementComponent>(VelocityDir, Speed);

    return Entity;
}

UEntity* CreatePlayer(UWorld* World) {
    if (!World) {
        assert(false);
        return nullptr;
    }

    const glm::vec3 Location{0.0f, 0.0f, 1.0f};
    const glm::vec3 Rotation{-90.0f, 0.0f, 0.0f};
    const glm::vec3 Scale{1.f, 1.f, 1.f};

    UEntity* Entity = World->CreateEntity();

    Entity->AddComponent<UTransformComponent>(Location, Rotation, Scale);
    Entity->AddComponent<UCameraComponent>();

    World->LocalPlayer = Entity;
    return Entity;
}

}  // namespace

void Arkanoid::Initialize(GLFWwindow* window) {
    BaseExcercise::Initialize(window);
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    UWorld* World = UWorld::CreateWorld();

    CreateEarth(World);
    CreatePlatform(World);
    CreatePlayer(World);

    USystem* ShaderSystem = World->CreateSystem<UShaderSystem>();
    USystem* RenderingSystem = World->CreateSystem<URenderingSystem>();
    USystem* StaticCameraSystem = World->CreateSystem<UStaticCameraSystem>();
    USystem* MovementSystem = World->CreateSystem<UMovementSystem>();

    World->Initialize();
}

void Arkanoid::Tick(float DeltaTime) {
    BaseExcercise::Tick(DeltaTime);

    auto World = UWorld::GetWorld();
    World->Update(DeltaTime);
}

void Arkanoid::Finalize() {
    auto World = UWorld::GetWorld();
    World->Finalize();

    World->DestroyWorld();
}
