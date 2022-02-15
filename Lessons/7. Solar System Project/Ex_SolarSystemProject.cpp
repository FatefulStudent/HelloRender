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

constexpr float DistanceMultiplier = 0.0005f;
namespace {
std::shared_ptr<ShaderProgram> CreateShaderProgram() {
    const std::string vertexPath =
        "Lessons/7. Solar System Project/shaders/shaderWithModelViewProj.vert";
    const std::string fragmentPath =
        "Lessons/7. Solar System Project/shaders/shaderWithTexture.frag";

    return std::make_shared<ShaderProgram>(vertexPath, fragmentPath);
}

std::shared_ptr<Camera> CreateCamera(GLFWwindow* window) {
    return std::make_shared<Camera>(window);
}

std::shared_ptr<Mesh> CreateMesh() {
    return std::make_shared<Mesh>();
}
}  // namespace

void Ex_SolarSystemProject::Initialize(GLFWwindow* window) {
    BaseExcercise::Initialize(window);
    {
        const CelestalBody SunModel = {"Resources/sunmap.jpg",
                                       0.0f * DistanceMultiplier, 1.0f};
        m_CelestalBodies.push_back(SunModel);
    }

    {
        const CelestalBody MercuryModel = {
            "Resources/mercurymap.jpg", 57950.0f * DistanceMultiplier, 1.0f};
        m_CelestalBodies.push_back(MercuryModel);
    }

    {
        const CelestalBody VenusModel = {"Resources/venusmap.jpg",
                                         108110.0f * DistanceMultiplier, 1.0f};
        m_CelestalBodies.push_back(VenusModel);
    }

    {
        const CelestalBody EarthModel = {"Resources/earthmap.jpg",
                                         149570.0f * DistanceMultiplier, 1.0f};
        m_CelestalBodies.push_back(EarthModel);
    }

    {
        const CelestalBody MarsModel = {"Resources/marsmap.jpg",
                                        227840.0f * DistanceMultiplier, 1.0f};
        m_CelestalBodies.push_back(MarsModel);
    }

    {
        const CelestalBody JupiterModel = {
            "Resources/jupitermap.jpg", 778140.0f * DistanceMultiplier, 1.0f};
        m_CelestalBodies.push_back(JupiterModel);
    }

    {
        const CelestalBody SaturnModel = {
            "Resources/saturnmap.jpg", 1427000.0f * DistanceMultiplier, 1.0f};
        m_CelestalBodies.push_back(SaturnModel);
    }

    {
        const CelestalBody UranusModel = {
            "Resources/uranusmap.jpg", 2870300.0f * DistanceMultiplier, 1.0f};
        m_CelestalBodies.push_back(UranusModel);
    }

    {
        const CelestalBody NeptuneModel = {
            "Resources/neptunemap.jpg", 4499900.0f * DistanceMultiplier, 1.0f};
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
    m_shaderProgram->use();
}

void Ex_SolarSystemProject::Tick(float deltaTime) {
    BaseExcercise::Tick(deltaTime);

    m_camera->Tick(deltaTime);

    for (int i = 0; i < m_CelestalBodies.size(); ++i) {
        const auto Body = m_CelestalBodies[i];
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model,
                               glm::vec3(Body.DistanceFromOrigin, 0.0f, 0.0f));

        model = glm::rotate(model, glm::radians(180.0f),
                            glm::vec3(1.0f, 0.f, 0.0f));

        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(m_camera->GetFov()),
                                      800.0f / 600.0f, 0.1f, 5000.0f);

        m_shaderProgram->use();
        m_shaderProgram->setMatrix("Model", model);
        m_shaderProgram->setMatrix("View", m_camera->GetViewMatrix());
        m_shaderProgram->setMatrix("Projection", projection);

        m_textures[i]->Bind();

        m_mesh->Draw();
    }
}
