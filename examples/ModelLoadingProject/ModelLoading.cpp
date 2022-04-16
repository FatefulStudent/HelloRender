#include "ModelLoading.h"

#include "Helper/Application.h"
#include "Helper/VertexData.h"
#include "Legacy/Camera3d.h"
// #include "Legacy/shaderInstance.h"
#include "Legacy/shaderProgram.h"

#include "Legacy/Shader.h"
#include "Legacy/Model.h"
#include "Legacy/Mesh.h"

/*
#include "World/World.h"
#include "Entity/Entity.h"
#include "Components/Component.h"
#include "Components/MeshComponent.h"
#include "Components/TextureComponent.h"
#include "Systems/System.h"
#include "Systems/RenderSystem.h"
*/

#include <GL/glew.h>
#include <stb_image.h>
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
std::shared_ptr<ShaderProgram> CreateShaderProgramSun() {
    const std::string vertexPath =
        "shaders/shaderForSun.vert";
    const std::string fragmentPath =
        "shaders/shaderForSun.frag";

    return std::make_shared<ShaderProgram>(vertexPath, fragmentPath);
}

std::shared_ptr<Camera3d> CreateCamera(GLFWwindow* window) {
    return std::make_shared<Camera3d>(window);
}

std::shared_ptr<Model> CreateModel(std::string&& Path) {
    return std::make_shared<Model>(Path.data());
}

void ComputeModelMatrix(glm::mat4& OutModelMatrix, const CelestalBody& Body) {

    //OutModelMatrix = glm::translate(
    //    OutModelMatrix, glm::vec3(Body.DistanceFromOrigin, 0.0f, 0.0f));

    OutModelMatrix = glm::rotate(OutModelMatrix, glm::radians(180.0f),
                                 glm::vec3(1.0f, 0.f, 0.0f));

    OutModelMatrix = glm::scale(
        OutModelMatrix, glm::vec3(Body.Radius, Body.Radius, Body.Radius));
}
}  // namespace

void ModelLoading::Initialize(GLFWwindow* window) {
    BaseExcercise::Initialize(window);

    /*
    auto World = UWorld::CreateWorld();

    UEntity* Entity = World->CreateEntity();

    Entity->AddComponent<UComponent>();
    Entity->AddComponent<UMeshComponent>();
    Entity->AddComponent<UTextureComponent>("res/sunmap.jpg", GL_TEXTURE0);

    USystem* RenderSystem = World->CreateSystem<URenderSystem>();
    World->Initialize();
    */
    stbi_set_flip_vertically_on_load(true);
    {
        const CelestalBody SunModel = {
            "res/sunmap.jpg", 10.0f};
        m_CelestalBodies.push_back(SunModel);
    }

    m_camera = CreateCamera(window);

    m_shaderProgramSun = CreateShaderProgramSun();

    m_model = CreateModel("res/backpack/backpack.obj");
}

void ModelLoading::Tick(float deltaTime) {
    BaseExcercise::Tick(deltaTime);

    m_camera->Tick(deltaTime);

    glm::vec3 SunColor = glm::vec3(1.0f, 1.0f, .8f);

    for (int i = 0; i < m_CelestalBodies.size(); ++i) {
        auto shaderProgram = m_shaderProgramSun;
        const auto Body = m_CelestalBodies[i];
        glm::mat4 model = glm::mat4(1.0f);

        // ComputeModelMatrix(model, Body);

        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(m_camera->GetFov()), 1.0f,
                                      0.1f, 500.0f);

        shaderProgram->use();
        shaderProgram->setMatrix("Model", model);
        shaderProgram->setMatrix("View", m_camera->GetViewMatrix());
        shaderProgram->setMatrix("Projection", projection);

        m_model->Draw(shaderProgram.get());

        /*
        auto World = UWorld::GetWorld();
        World->Update();
        */
    }
}

void ModelLoading::Finalize() {
    /*
    auto World = UWorld::GetWorld();
    World->Finalize();

    World->DestroyWorld();*/
}
