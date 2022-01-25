#include "Ex_Transforms.h"

#include "Helper/Application.h"
#include "Helper/VertexData.h"
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

namespace {
std::shared_ptr<ShaderProgram> CreateShaderProgram() {
    const std::string vertexPath =
        "Lessons/Transforms/shaders/shaderWithTransform.vert";
    const std::string fragmentPath =
        "Lessons/Transforms/shaders/shaderWithTexture.frag";

    return std::make_shared<ShaderProgram>(vertexPath, fragmentPath);
}

std::shared_ptr<Mesh> CreateMesh() {
    std::vector<VertexData_PosColorTexture> vertices = {
        // positions          // colors           // texture coords
        {{0.5f, 0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},    // UR
        {{0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},   // DR
        {{-0.5f, -0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},  // DL
        {{-0.5f, 0.5f}, {1.0f, 1.0f, 0.0f}, {0.0f, 1.0f}},   // UL
    };

    std::vector<unsigned> indices = {
        0, 1, 3,  // first triangle
        1, 2, 3,  // second triangle
    };

    return std::make_shared<Mesh>(std::move(vertices), std::move(indices));
}
}  // namespace

void Ex_Transforms::Initialize(GLFWwindow* window) {
    BaseExcercise::Initialize(window);

    m_texture1 =
        std::make_shared<Texture>("Resources/woodContainer.jpg", GL_TEXTURE0);
    m_texture2 =
        std::make_shared<Texture>("Resources/awesomeFace.png", GL_TEXTURE1);

    m_mesh = CreateMesh();

    m_shaderProgram = CreateShaderProgram();
    m_shaderProgram->use();
    m_shaderProgram->setInt("Texture1", 0);
    m_shaderProgram->setInt("Texture2", 1);
}

void Ex_Transforms::Tick() {
    BaseExcercise::Tick();

    glm::mat4 trans1 = glm::mat4(1.0f);
    trans1 = glm::rotate(trans1, 3 * (float)glfwGetTime(),
                         glm::vec3(0.0f, 0.0f, 1.0f));
    trans1 = glm::translate(trans1, glm::vec3(0.5f, -0.5f, 0.0f));

    m_shaderProgram->use();
    m_shaderProgram->setMatrix("Transform", trans1);

    m_texture1->Bind();
    m_texture2->Bind();

    m_mesh->Draw();

    float sinValue = sin(glfwGetTime());

    glm::mat4 trans2 = glm::mat4(1.0f);
    trans2 = glm::translate(trans2, glm::vec3(-0.5f, 0.5f, 0.0f));
    trans2 = glm::scale(trans2, glm::vec3(sinValue, sinValue, sinValue));
    m_shaderProgram->setMatrix("Transform", trans2);
    m_mesh->Draw();
}
