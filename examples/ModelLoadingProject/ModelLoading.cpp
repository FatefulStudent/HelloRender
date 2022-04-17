#include "ModelLoading.h"

#include "Helper/Application.h"
#include "Helper/VertexData.h"
#include "Legacy/Camera3d.h"
// #include "Legacy/shaderInstance.h"
#include "Legacy/shaderProgram.h"

#include "Legacy/Shader.h"
#include "Legacy/Model.h"
#include "Legacy/Mesh.h"

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

}  // namespace

void ModelLoading::Initialize(GLFWwindow* window) {
    BaseExcercise::Initialize(window);

    stbi_set_flip_vertically_on_load(true);

    m_camera = CreateCamera(window);

    m_shaderProgramSun = CreateShaderProgramSun();

    m_model = CreateModel("res/backpack/backpack.obj");
}

void ModelLoading::Tick(float deltaTime) {
    BaseExcercise::Tick(deltaTime);

    m_camera->Tick(deltaTime);

     glm::mat4 model = glm::mat4(1.0f);

    glm::mat4 projection = glm::mat4(1.0f);
    projection =
        glm::perspective(glm::radians(m_camera->GetFov()), 1.0f, 0.1f, 500.0f);

    m_shaderProgramSun->use();
    m_shaderProgramSun->setMatrix("Model", model);
    m_shaderProgramSun->setMatrix("View", m_camera->GetViewMatrix());
    m_shaderProgramSun->setMatrix("Projection", projection);

    m_model->Draw(nullptr);
}

void ModelLoading::Finalize() {
}
