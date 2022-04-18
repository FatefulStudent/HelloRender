#include "Arkanoid.h"

#include "Helper/Application.h"
#include "Legacy/Camera3d.h"

#include "World/World.h"
#include "Entity/Entity.h"
#include "Components/Component.h"
#include "Components/ShaderComponent.h"
#include "Components/ModelComponent.h"

#include "Systems/System.h"
#include "Systems/RenderingSystem.h"
#include "Systems/ShaderSystem.h"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <cassert>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <vector>


namespace {

std::shared_ptr<Camera3d> CreateCamera(GLFWwindow* window) {
    return std::make_shared<Camera3d>(window);
}

}  // namespace

void Arkanoid::Initialize(GLFWwindow* window) {
    BaseExcercise::Initialize(window);
    glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
    auto World = UWorld::CreateWorld();
    
    UEntity* Entity = World->CreateEntity();

    Entity->AddComponent<UComponent>();
    Entity->AddComponent<UShaderComponent>("shaders/shaderForSun.vert",
                                           "shaders/shaderForSun.frag");
    Entity->AddComponent<UModelComponent>("res/backpack/backpack.obj");

    USystem* ShaderSystem = World->CreateSystem<UShaderSystem>();
    USystem* RenderingSystem = World->CreateSystem<URenderingSystem>();

    World->Initialize();

    m_camera = CreateCamera(window);
}

void Arkanoid::Tick(float deltaTime) {
    BaseExcercise::Tick(deltaTime);

    m_camera->Tick(deltaTime);

    glm::mat4 model = glm::mat4(1.0f);

    glm::mat4 projection = glm::mat4(1.0f);
    projection =
        glm::perspective(glm::radians(m_camera->GetFov()), 1.0f, 0.1f, 500.0f);

    auto World = UWorld::GetWorld();

    // Should be in a separate system
    {
        auto Entities = World->GetAllEntitiesWithComponents({EComponentClass::UShaderComponent});
        for each (UEntity* Entity in Entities) {
            UShaderComponent* ShaderComponent =
                Entity->GetComponentOfClass<UShaderComponent>();

            ShaderComponent->Model = model;
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
