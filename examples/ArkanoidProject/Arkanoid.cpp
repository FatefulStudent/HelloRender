#include "Arkanoid.h"

#include "Helper/Application.h"

#include "Components/Component.h"
#include "Components/ModelComponent.h"
#include "Components/ShaderComponent.h"
#include "Components/TransformComponent.h"
#include "Components/CameraComponent.h"
#include "Components/MovementComponent.h"
#include "Components/SimpleCollisionComponent.h"
#include "Entity/Entity.h"
#include "World/World.h"

#include "Systems/RenderingSystem.h"
#include "Systems/ShaderSystem.h"
#include "Systems/System.h"
#include "Systems/StaticCameraSystem.h"
#include "Systems/MovementSystem.h"
#include "Systems/SimpleCollisionSystem.h"

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
    const FTransform Transform {Location, Rotation, Scale};
    const std::string ModelPath("res/platform/platform.obj");
    const std::string VertShaderPath("shaders/simpleShader.vert");
    const std::string FragShaderPath("shaders/simpleShader.frag");

    
    const glm::vec3 VelocityDir{-1.0f, 2.0f, 0.0f};
    const float Speed = 20.0f;
    
    const ECollisionShape CollisionShape = ECollisionShape::Rectangle;
    const float Width = 5.0f;
    const float Height = 1.f;

    UEntity* Entity = World->CreateEntity(std::string("Platform"));

    Entity->AddComponent<UShaderComponent>(VertShaderPath, 
                                           FragShaderPath);
    Entity->AddComponent<UModelComponent>(ModelPath);
    Entity->AddComponent<UTransformComponent>(Transform);
    Entity->AddComponent<UMovementComponent>(VelocityDir, Speed);
    Entity->AddComponent<USimpleCollisionComponent>(CollisionShape, Width,
                                                    Height);

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
    const FTransform Transform {Location, Rotation, Scale};

    const glm::vec3 VelocityDir{1.0f, 2.0f, 0.0f};
    const float Speed = 20.0f;
    const std::string ModelPath("res/earth/earth.obj");
    const std::string VertShaderPath("shaders/simpleShader.vert");
    const std::string FragShaderPath("shaders/simpleShader.frag");

    const ECollisionShape CollisionShape = ECollisionShape::Circle;
    const float CircleRadius = 1.0f;

    UEntity* Entity = World->CreateEntity(std::string("EarthBall"));

    Entity->AddComponent<UShaderComponent>(VertShaderPath, FragShaderPath);
    Entity->AddComponent<UModelComponent>(ModelPath);
    Entity->AddComponent<UTransformComponent>(Transform);
    Entity->AddComponent<UMovementComponent>(VelocityDir, Speed);
    Entity->AddComponent<USimpleCollisionComponent>(CollisionShape,
                                                    CircleRadius);

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
    const FTransform Transform {Location, Rotation, Scale};

    UEntity* Entity = World->CreateEntity(std::string("Player"));

    Entity->AddComponent<UTransformComponent>(Transform);
    Entity->AddComponent<UCameraComponent>();

    UWorld::LocalPlayer = Entity;
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

    USystem* CollisionSystem = World->CreateSystem<USimpleCollisionSystem>();
    USystem* MovementSystem = World->CreateSystem<UMovementSystem>();
    USystem* ShaderSystem = World->CreateSystem<UShaderSystem>();
    USystem* RenderingSystem = World->CreateSystem<URenderingSystem>();
    USystem* StaticCameraSystem = World->CreateSystem<UStaticCameraSystem>();

    World->Initialize();
}

void Arkanoid::Tick(double DeltaTime) {
    BaseExcercise::Tick(DeltaTime);

    auto World = UWorld::GetWorld();
    World->Update(DeltaTime);
}

void Arkanoid::Finalize() {
    auto World = UWorld::GetWorld();
    World->Finalize();

    UWorld::DestroyWorld();
}
