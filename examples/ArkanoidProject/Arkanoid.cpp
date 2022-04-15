#include "Arkanoid.h"

#include "Helper/Application.h"
#include "Helper/VertexData.h"
#include "Camera2d.h"
#include "mesh.h"
#include "shaderInstance.h"
#include "shaderProgram.h"
#include "texture.h"

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

std::shared_ptr<Camera2d> CreateCamera() {
    return std::make_shared<Camera2d>();
}

std::shared_ptr<Mesh> CreateMesh() {
    return std::make_shared<Mesh>();
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

void Arkanoid::Initialize(GLFWwindow* window) {
    BaseExcercise::Initialize(window);
    {
        const CelestalBody SunModel = {
            "res/sunmap.jpg", 10.0f};
        m_CelestalBodies.push_back(SunModel);
    }

    for (int i = 0; i < m_CelestalBodies.size(); ++i) {
        const auto TexturePath = m_CelestalBodies[i].TexturePath;
        m_textures.push_back(
            std::make_shared<Texture>(TexturePath, GL_TEXTURE0 + i));
    }

    m_camera = CreateCamera();

    m_mesh = CreateMesh();

    m_shaderProgramSun = CreateShaderProgramSun();
}

void Arkanoid::Tick(float deltaTime) {
    BaseExcercise::Tick(deltaTime);

    m_camera->Tick(deltaTime);

    glm::vec3 SunColor = glm::vec3(1.0f, 1.0f, .8f);

    for (int i = 0; i < m_CelestalBodies.size(); ++i) {
        auto shaderProgram = m_shaderProgramSun;
        const auto Body = m_CelestalBodies[i];
        glm::mat4 model = glm::mat4(1.0f);

        ComputeModelMatrix(model, Body);

        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(m_camera->GetFov()), 1.0f,
                                      0.1f, 500.0f);

        shaderProgram->use();
        shaderProgram->setMatrix("Model", model);
        shaderProgram->setMatrix("View", m_camera->GetViewMatrix());
        shaderProgram->setMatrix("Projection", projection);

        m_textures[i]->Bind();

        m_mesh->Draw();
    }
}
