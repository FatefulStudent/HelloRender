#include "Arkanoid.h"

#include "Helper/Application.h"

#include "Components/Component.h"
#include "Components/ModelComponent.h"
#include "Components/ShaderComponent.h"
#include "Components/TransformComponent.h"
#include "Components/CameraComponent.h"
#include "Entity/Entity.h"
#include "World/World.h"

#include "Systems/RenderingSystem.h"
#include "Systems/ShaderSystem.h"
#include "Systems/System.h"
#include "Systems/StaticCameraSystem.h"

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

UEntity* CreateSun(UWorld* World) {
    if (!World) {
        assert(false);
        return nullptr;
    }

    const glm::vec3 Location{-5.0f, 0.0f, 0.0f};
    const glm::vec3 Rotation{0.0f, 0.0f, 0.0f};
    const glm::vec3 Scale{1.f, 1.f, 1.f};
    const std::string ModelPath("res/sun/sun.obj");
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
    const std::string ModelPath("res/earth/earth.obj");
    const std::string VertShaderPath("shaders/shaderForSun.vert");
    const std::string FragShaderPath("shaders/shaderForSun.frag");

    UEntity* Entity = World->CreateEntity();

    Entity->AddComponent<UShaderComponent>(VertShaderPath, FragShaderPath);
    Entity->AddComponent<UModelComponent>(ModelPath);
    Entity->AddComponent<UTransformComponent>(Location, Rotation, Scale);

    return Entity;
}

UEntity* CreatePlayer(UWorld* World) {
    if (!World) {
        assert(false);
        return nullptr;
    }

    const glm::vec3 Location{0.0f, 0.0f, 40.0f};
    const glm::vec3 Rotation{-90.0f, 0.0f, 0.0f};
    const glm::vec3 Scale{1.f, 1.f, 1.f};

    UEntity* Entity = World->CreateEntity();

    Entity->AddComponent<UTransformComponent>(Location, Rotation, Scale);
    Entity->AddComponent<UCameraComponent>();

    return Entity;
}

}  // namespace

void Arkanoid::Initialize(GLFWwindow* window) {
    BaseExcercise::Initialize(window);
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    UWorld* World = UWorld::CreateWorld();

    CreateEarth(World);
    CreateSun(World);
    CreatePlayer(World);

    USystem* ShaderSystem = World->CreateSystem<UShaderSystem>();
    USystem* RenderingSystem = World->CreateSystem<URenderingSystem>();
    USystem* StaticCameraSystem = World->CreateSystem<UStaticCameraSystem>();

    World->Initialize();
}

void Arkanoid::Tick(float deltaTime) {
    BaseExcercise::Tick(deltaTime);

    
    auto World = UWorld::GetWorld();

    auto CameraEntities = World->GetAllEntitiesWithComponents(
        {EComponentClass::UCameraComponent});

    auto Camera = CameraEntities[0]->GetComponentOfClass<UCameraComponent>();
    // Should be in a separate system
    {
        auto Entities = World->GetAllEntitiesWithComponents(
            {EComponentClass::UShaderComponent,
             EComponentClass::UTransformComponent});

        for each (UEntity* Entity in Entities) {
            UShaderComponent* ShaderComponent =
                Entity->GetComponentOfClass<UShaderComponent>();
            if (!ShaderComponent) {
                assert(false);
                continue;
            }

            UTransformComponent* TransformComponent =
                Entity->GetComponentOfClass<UTransformComponent>();
            if (!TransformComponent) {
                assert(false);
                continue;
            }

            glm::mat4 TransformMatrix(1.0f);

            {
                
                TransformMatrix = glm::translate(
                    TransformMatrix, glm::vec3(TransformComponent->Position));

                float RotationAroundItself = glfwGetTime() * 10.0f;

                // pitch
                TransformMatrix =
                    glm::rotate(TransformMatrix,
                                glm::radians(TransformComponent->Rotation.z),
                                glm::vec3(1.0f, 0.f, 0.0f));

                // yaw
                TransformMatrix =
                    glm::rotate(TransformMatrix,
                                glm::radians(TransformComponent->Rotation.x),
                                glm::vec3(0.0f, 1.f, 0.0f));

                // roll
                TransformMatrix =
                    glm::rotate(TransformMatrix,
                                glm::radians(TransformComponent->Rotation.y),
                                glm::vec3(0.0f, 0.f, 1.0f));

                TransformMatrix =
                    glm::scale(TransformMatrix, TransformComponent->Scale);
            }

            ShaderComponent->Model = TransformMatrix;
            ShaderComponent->View = Camera->View;
            ShaderComponent->Projection = Camera->Projection;
        }
    }

    World->Update();
}

void Arkanoid::Finalize() {
    auto World = UWorld::GetWorld();
    World->Finalize();

    World->DestroyWorld();
}
