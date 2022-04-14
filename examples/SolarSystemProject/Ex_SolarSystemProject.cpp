#include "Ex_SolarSystemProject.h"

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

constexpr float DistanceMultiplier = 0.000001f;
constexpr float RadiusMultiplier = 0.0002f;
constexpr float AdditionalSunRadiusDivider = 7.f;
constexpr bool bRotateAroundSun = false;
constexpr float RotationAroundAxisMultiplier = 50.0f;
constexpr float RotationAroundSunMultiplier = 1500.0f;

constexpr float AmbientStrength = 0.05f;
constexpr float DiffuseStrength = 1.0f;
constexpr float SpecularStrength = 1.7f;
constexpr int Shininess = 16;

namespace {
std::shared_ptr<ShaderProgram> CreateShaderProgram() {
    const std::string vertexPath =
        "shaders/shaderWithModelViewProj.vert";
    const std::string fragmentPath =
        "shaders/shaderWithLighting.frag";

    return std::make_shared<ShaderProgram>(vertexPath, fragmentPath);
}
std::shared_ptr<ShaderProgram> CreateShaderProgramSun() {
    const std::string vertexPath =
        "shaders/shaderForSun.vert";
    const std::string fragmentPath =
        "shaders/shaderForSun.frag";

    return std::make_shared<ShaderProgram>(vertexPath, fragmentPath);
}

std::shared_ptr<Camera> CreateCamera(GLFWwindow* window) {
    return std::make_shared<Camera>(window);
}

std::shared_ptr<Mesh> CreateMesh() {
    return std::make_shared<Mesh>();
}

void ComputeModelMatrix(glm::mat4& OutModelMatrix, const CelestalBody& Body) {
    if (bRotateAroundSun) {
        float RotationAroundSun = 0.0f;

        if (Body.DistanceFromOrigin > 1.0f)
            RotationAroundSun = glfwGetTime() * RotationAroundSunMultiplier /
                                Body.DistanceFromOrigin;

        OutModelMatrix =
            glm::rotate(OutModelMatrix, glm::radians(RotationAroundSun),
                        glm::vec3(0.0f, 1.f, 0.0f));
    }

    OutModelMatrix = glm::translate(
        OutModelMatrix, glm::vec3(Body.DistanceFromOrigin, 0.0f, 0.0f));

    OutModelMatrix = glm::rotate(OutModelMatrix, glm::radians(180.0f),
                                 glm::vec3(1.0f, 0.f, 0.0f));

    float RotationAroundItself =
        glfwGetTime() * RotationAroundAxisMultiplier / Body.Radius;
    OutModelMatrix =
        glm::rotate(OutModelMatrix, glm::radians(RotationAroundItself),
                    glm::vec3(0.0f, 1.f, 0.0f));

    OutModelMatrix = glm::scale(
        OutModelMatrix, glm::vec3(Body.Radius, Body.Radius, Body.Radius));
}
}  // namespace

void Ex_SolarSystemProject::Initialize(GLFWwindow* window) {
    BaseExcercise::Initialize(window);
    {
        const CelestalBody SunModel = {
            "res/sunmap.jpg", 0.0f * DistanceMultiplier,
            1392000.0f * RadiusMultiplier / AdditionalSunRadiusDivider};
        m_CelestalBodies.push_back(SunModel);
    }

    {
        const CelestalBody MercuryModel = {"res/mercurymap.jpg",
                                           57950000.0 * DistanceMultiplier,
                                           4800.0f * RadiusMultiplier};
        m_CelestalBodies.push_back(MercuryModel);
    }

    {
        const CelestalBody VenusModel = {"res/venusmap.jpg",
                                         108110000.0 * DistanceMultiplier,
                                         12100.0f * RadiusMultiplier};
        m_CelestalBodies.push_back(VenusModel);
    }

    {
        const CelestalBody EarthModel = {"res/earthmap.jpg",
                                         149570000.0 * DistanceMultiplier,
                                         12700.0f * RadiusMultiplier};
        m_CelestalBodies.push_back(EarthModel);
    }

    {
        const CelestalBody MarsModel = {"res/marsmap.jpg",
                                        227840000.0 * DistanceMultiplier,
                                        6700.0f * RadiusMultiplier};
        m_CelestalBodies.push_back(MarsModel);
    }

    {
        const CelestalBody JupiterModel = {"res/jupitermap.jpg",
                                           778140000.0 * DistanceMultiplier,
                                           142900.0f * RadiusMultiplier};
        m_CelestalBodies.push_back(JupiterModel);
    }

    {
        const CelestalBody SaturnModel = {"res/saturnmap.jpg",
                                          1427000000.0 * DistanceMultiplier,
                                          116438.0f * RadiusMultiplier};
        m_CelestalBodies.push_back(SaturnModel);
    }

    {
        const CelestalBody UranusModel = {"res/uranusmap.jpg",
                                          2870300000.0 * DistanceMultiplier,
                                          46940.0f * RadiusMultiplier};
        m_CelestalBodies.push_back(UranusModel);
    }

    {
        const CelestalBody NeptuneModel = {"res/neptunemap.jpg",
                                           4499900000.0 * DistanceMultiplier,
                                           45400.0f * RadiusMultiplier};
        m_CelestalBodies.push_back(NeptuneModel);
    }

    for (int i = 0; i < m_CelestalBodies.size(); ++i) {
        const auto TexturePath = m_CelestalBodies[i].TexturePath;
        m_textures.push_back(
            std::make_shared<Texture>(TexturePath, GL_TEXTURE0 + i));
    }

    m_camera = CreateCamera(window);

    m_mesh = CreateMesh();

    m_shaderProgram = CreateShaderProgram();
    m_shaderProgramSun = CreateShaderProgramSun();
}

void Ex_SolarSystemProject::Tick(float deltaTime) {
    BaseExcercise::Tick(deltaTime);

    m_camera->Tick(deltaTime);

    glm::vec3 SunColor = glm::vec3(1.0f, 1.0f, .8f);

    for (int i = 0; i < m_CelestalBodies.size(); ++i) {
        auto shaderProgram = i == 0 ? m_shaderProgramSun : m_shaderProgram;
        const auto Body = m_CelestalBodies[i];
        glm::mat4 model = glm::mat4(1.0f);

        ComputeModelMatrix(model, Body);

        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(m_camera->GetFov()), 1.0f,
                                      0.1f, 500000.0f);

        shaderProgram->use();
        shaderProgram->setMatrix("Model", model);
        shaderProgram->setMatrix("View", m_camera->GetViewMatrix());
        shaderProgram->setMatrix("Projection", projection);

        if (i != 0) {
            shaderProgram->setVec3("lightPos", glm::vec3(.0f));

            shaderProgram->setVec3("objectColor", glm::vec3(1.0f, 1.0f, 1.0f));
            shaderProgram->setFloat("ambientStrength", AmbientStrength);
            shaderProgram->setFloat("diffuseStrength", DiffuseStrength);
            shaderProgram->setFloat("specularStrength", SpecularStrength);
            shaderProgram->setInt("shininess", Shininess);
            shaderProgram->setInt("index", i);
            shaderProgram->setVec3("lightColor", SunColor);
            shaderProgram->setVec3("viewPos", m_camera->GetPosition());
        }
        m_textures[i]->Bind();

        m_mesh->Draw();
    }
}
