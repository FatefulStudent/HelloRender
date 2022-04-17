#include "Arkanoid.h"

#include "Helper/Application.h"
#include "Helper/VertexData.h"
#include "Legacy/Camera3d.h"
#include "Legacy/shaderInstance.h"
#include "Legacy/shaderProgram.h"
#include "Legacy/Model.h"

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

constexpr float AmbientStrength = 0.05f;
constexpr float DiffuseStrength = 1.0f;
constexpr float SpecularStrength = 1.7f;
constexpr int Shininess = 16;

namespace {

std::shared_ptr<Camera3d> CreateCamera(GLFWwindow* window) {
    return std::make_shared<Camera3d>(window);
}

}  // namespace

void Arkanoid::Initialize(GLFWwindow* window) {
    BaseExcercise::Initialize(window);
    glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
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
        auto Entity = World->GetFirstEntity();
        UShaderComponent* ShaderComponent =
            Entity->GetComponentOfClass<UShaderComponent>();

        ShaderComponent->Model = model;
        ShaderComponent->View = m_camera->GetViewMatrix();
        ShaderComponent->Projection = projection;
    }

    World->Update();
}

void Arkanoid::Finalize() {
    auto World = UWorld::GetWorld();
    World->Finalize();

    World->DestroyWorld();
}
