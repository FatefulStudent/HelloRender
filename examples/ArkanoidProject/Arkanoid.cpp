#include "Arkanoid.h"

#include "Helper/Application.h"
#include "Legacy/Camera2d.h"

#include "Components/Component.h"
#include "Components/ModelComponent.h"
#include "Components/ShaderComponent.h"
#include "Components/TransformComponent.h"
#include "Entity/Entity.h"
#include "World/World.h"

#include "Systems/RenderingSystem.h"
#include "Systems/ShaderSystem.h"
#include "Systems/System.h"

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

std::shared_ptr<Camera2d> CreateCamera(GLFWwindow* window) {
    return std::make_shared<Camera2d>();
}

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

}  // namespace

void Arkanoid::Initialize(GLFWwindow* window) {
    BaseExcercise::Initialize(window);
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    UWorld* World = UWorld::CreateWorld();

    CreateEarth(World);
    CreateSun(World);

    USystem* ShaderSystem = World->CreateSystem<UShaderSystem>();
    USystem* RenderingSystem = World->CreateSystem<URenderingSystem>();
    

    World->Initialize();

    m_camera = CreateCamera(window);
}

void Arkanoid::Tick(float deltaTime) {
    BaseExcercise::Tick(deltaTime);

    m_camera->Tick(deltaTime);

    glm::mat4 projection = glm::mat4(1.0f);
    projection =
        glm::perspective(glm::radians(m_camera->GetFov()), 1.0f, 0.1f, 500.0f);

    auto World = UWorld::GetWorld();

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
            ShaderComponent->View = m_camera->GetViewMatrix();
            ShaderComponent->Projection = projection;
        }
    }

    World->Update();
}

void Arkanoid::Finalize() {
    auto World = UWorld::GetWorld();
    World->Finalize();

    World->DestroyWorld();
}
