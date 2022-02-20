#include "Ex_Materials.h"

#include "Helper/Application.h"
#include "Helper/VertexData.h"
#include "camera.h"
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

constexpr float DistanceMultiplier = 0.0000001f;
constexpr float RadiusMultiplier = 0.0002f;
constexpr float AdditionalSunRadiusDivider = 50.f;
constexpr bool bRotateAroundSun = false;
constexpr bool bRotateAroundSelf = true;
constexpr float RotationAroundAxisMultiplier = 50.0f;
constexpr float RotationAroundSunMultiplier = 1500.0f;

constexpr int Shininess = 16;

constexpr glm::vec3 InitialCameraPosition = {7.5, 0.0, 30.0};

namespace {
std::shared_ptr<ShaderProgram> CreateShaderProgram() {
    const std::string vertexPath =
        "Lessons/8. Materials/shaders/shaderWithLighting.vert";
    const std::string fragmentPath =
        "Lessons/8. Materials/shaders/shaderWithLighting.frag";

    return std::make_shared<ShaderProgram>(vertexPath, fragmentPath);
}
std::shared_ptr<ShaderProgram> CreateShaderProgramSun() {
    const std::string vertexPath =
        "Lessons/8. Materials/shaders/shaderForLightSource.vert";
    const std::string fragmentPath =
        "Lessons/8. Materials/shaders/shaderForLightSource.frag";

    return std::make_shared<ShaderProgram>(vertexPath, fragmentPath);
}

std::shared_ptr<Camera> CreateCamera(GLFWwindow* window) {
    return std::make_shared<Camera>(window);
}

std::shared_ptr<Mesh> CreateMesh() {
    return std::make_shared<Mesh>();
}

void ComputeModelMatrix(glm::mat4& OutModelMatrix,
                        const CelestalBody& Body,
                        bool bJump) {
    if (bRotateAroundSun) {
        float RotationAroundSun = 0.0f;

        if (Body.DistanceFromOrigin > 1.0f)
            RotationAroundSun = glfwGetTime() * RotationAroundSunMultiplier /
                                Body.DistanceFromOrigin;

        OutModelMatrix =
            glm::rotate(OutModelMatrix, glm::radians(RotationAroundSun),
                        glm::vec3(0.0f, 1.f, 0.0f));
    }

    float yOffset = 0.0f;
    if (bJump) {
        yOffset = 10.0f * sin(glfwGetTime() * 3.0f);
    }

    OutModelMatrix = glm::translate(
        OutModelMatrix, glm::vec3(Body.DistanceFromOrigin, yOffset, 0.0f));

    OutModelMatrix = glm::rotate(OutModelMatrix, glm::radians(180.0f),
                                 glm::vec3(1.0f, 0.f, 0.0f));

    if (bRotateAroundSelf) {
        float RotationAroundItself =
            glfwGetTime() * RotationAroundAxisMultiplier / Body.Radius;
        OutModelMatrix =
            glm::rotate(OutModelMatrix, glm::radians(RotationAroundItself),
                        glm::vec3(0.0f, 1.f, 0.0f));
    }

    OutModelMatrix = glm::scale(
        OutModelMatrix, glm::vec3(Body.Radius, Body.Radius, Body.Radius));
}
}  // namespace

void Ex_Materials::Initialize(GLFWwindow* window) {
    BaseExcercise::Initialize(window);
    {
        const CelestalBody SunModel = {
            "Resources/sunmap.jpg", 0.0f * DistanceMultiplier,
            1392000.0f * RadiusMultiplier / AdditionalSunRadiusDivider};
        m_CelestalBodies.push_back(SunModel);
    }

    {
        const CelestalBody EarthModel = {"Resources/earthmap.jpg",
                                         149570000.0 * DistanceMultiplier,
                                         12700.0f * RadiusMultiplier};
        m_CelestalBodies.push_back(EarthModel);
    }

    for (int i = 0; i < m_CelestalBodies.size(); ++i) {
        const auto TexturePath = m_CelestalBodies[i].TexturePath;
        m_textures.push_back(
            std::make_shared<Texture>(TexturePath, GL_TEXTURE0 + i));
    }

    m_camera = CreateCamera(window);
    m_camera->SetPosition(InitialCameraPosition);

    m_mesh = CreateMesh();

    m_shaderProgram = CreateShaderProgram();
    m_shaderProgramSun = CreateShaderProgramSun();
}

void Ex_Materials::Tick(float deltaTime) {
    BaseExcercise::Tick(deltaTime);

    m_camera->Tick(deltaTime);

    glm::vec3 SunColor = glm::vec3(1.0f, 1.0f, .8f);

    for (int i = 0; i < m_CelestalBodies.size(); ++i) {
        auto shaderProgram = i == 0 ? m_shaderProgramSun : m_shaderProgram;
        const auto Body = m_CelestalBodies[i];
        glm::mat4 model = glm::mat4(1.0f);

        ComputeModelMatrix(model, Body, i != 0);

        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(m_camera->GetFov()), 1.0f,
                                      0.1f, 500000.0f);

        shaderProgram->use();
        shaderProgram->setMatrix("Model", model);
        shaderProgram->setMatrix("View", m_camera->GetViewMatrix());
        shaderProgram->setMatrix("Projection", projection);
        shaderProgram->setVec3("lightColor", SunColor);

        glm::vec3 lightColor;
        lightColor.x = sin(glfwGetTime() * 2.0f);
        lightColor.y = sin(glfwGetTime() * 0.7f);
        lightColor.z = sin(glfwGetTime() * 1.3f);

        if (i == 0) {
            shaderProgram->setVec3("lightColor", lightColor);
        } else {
            shaderProgram->setVec3("viewPos", m_camera->GetPosition());

            glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f);
            glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f);

            shaderProgram->setVec3("light.position", glm::vec3(.0f));
            shaderProgram->setVec3("light.ambient", ambientColor);
            shaderProgram->setVec3("light.diffuse", diffuseColor);
            shaderProgram->setVec3("light.specular", {1.0f, 1.0f, 1.0f});

            shaderProgram->setVec3("material.ambient", {1.0f, 0.5f, 0.31f});
            shaderProgram->setVec3("material.diffuse", {1.0f, 0.5f, 0.31f});
            shaderProgram->setVec3("material.specular", {0.5f, 0.5f, 0.5f});
            shaderProgram->setFloat("material.shininess", 2.0f);
        }
        m_textures[i]->Bind();

        m_mesh->Draw();
    }
}
