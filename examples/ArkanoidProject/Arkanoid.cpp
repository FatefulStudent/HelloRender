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

Entity* CreatePlatform(World* World) {
    if (!World) {
        assert(false);
        return nullptr;
    }

    const glm::vec3 location{-5.0f, 0.0f, 0.0f};
    const glm::vec3 rotation{-90.0f, 0.0f, 0.0f};
    const glm::vec3 scale{1.f, 1.f, 1.f};
    const FTransform transform {location, rotation, scale};
    const std::string modelPath("res/platform/platform.obj");
    const std::string vertShaderPath("shaders/simpleShader.vert");
    const std::string fragShaderPath("shaders/simpleShader.frag");

    
    const glm::vec3 velocityDir{-1.0f, 2.0f, 0.0f};
    const float speed = 20.0f;
    
    const ECollisionShape collisionShape = ECollisionShape::Rectangle;
    const float width = 5.0f;
    const float height = 1.f;

    Entity* Entity = World->CreateEntity(std::string("Platform"));

    Entity->AddComponent<UShaderComponent>(vertShaderPath, 
                                           fragShaderPath);
    Entity->AddComponent<ModelComponent>(modelPath);
    Entity->AddComponent<TransformComponent>(transform);
    Entity->AddComponent<MovementComponent>(velocityDir, speed);
    Entity->AddComponent<SimpleCollisionComponent>(collisionShape, width,
                                                    height);

    return Entity;
}

Entity* CreateEarth(World* World) {
    if (!World) {
        assert(false);
        return nullptr;
    }

    const glm::vec3 location{10.0f, 0.0f, 0.0f};
    const glm::vec3 rotation{0.0f, 180.0f, 0.0f};
    const glm::vec3 scale{1.f, 1.f, 1.f};
    const FTransform transform {location, rotation, scale};

    const glm::vec3 velocityDir{1.0f, 2.0f, 0.0f};
    const float speed = 20.0f;
    const std::string modelPath("res/earth/earth.obj");
    const std::string vertShaderPath("shaders/simpleShader.vert");
    const std::string fragShaderPath("shaders/simpleShader.frag");

    const ECollisionShape shape = ECollisionShape::Circle;
    const float circleRadius = 1.0f;

    Entity* entity = World->CreateEntity(std::string("EarthBall"));

    entity->AddComponent<UShaderComponent>(vertShaderPath, fragShaderPath);
    entity->AddComponent<ModelComponent>(modelPath);
    entity->AddComponent<TransformComponent>(transform);
    entity->AddComponent<MovementComponent>(velocityDir, speed);
    entity->AddComponent<SimpleCollisionComponent>(shape,
                                                    circleRadius);

    return entity;
}

Entity* CreatePlayer(World* World) {
    if (!World) {
        assert(false);
        return nullptr;
    }

    const glm::vec3 Location{0.0f, 0.0f, 1.0f};
    const glm::vec3 Rotation{-90.0f, 0.0f, 0.0f};
    const glm::vec3 Scale{1.f, 1.f, 1.f};
    const FTransform Transform {Location, Rotation, Scale};

    Entity* Entity = World->CreateEntity(std::string("Player"));

    Entity->AddComponent<TransformComponent>(Transform);
    Entity->AddComponent<CameraComponent>();

    World::localPlayer = Entity;
    return Entity;
}

}  // namespace

void Arkanoid::Initialize(GLFWwindow* window) {
    BaseExcercise::Initialize(window);
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    World* World = World::CreateWorld();

    CreateEarth(World);
    CreatePlatform(World);
    CreatePlayer(World);

    World->CreateSystem<SimpleCollisionSystem>();
    World->CreateSystem<MovementSystem>();
    World->CreateSystem<ShaderSystem>();
    World->CreateSystem<RenderingSystem>();
    World->CreateSystem<StaticCameraSystem>();

    World->Initialize();
}

void Arkanoid::Tick(double deltaTime) {
    BaseExcercise::Tick(deltaTime);

    auto World = World::GetWorld();
    World->Update(deltaTime);
}

void Arkanoid::Finalize() {
    auto World = World::GetWorld();
    World->Finalize();

    World::DestroyWorld();
}
