#include "Ex_Transforms.h"

#include "Helper/ApplicationHelper.h"
#include "Helper/VertexData.h"
#include "mesh.h"
#include "shaderInstance.h"
#include "shaderProgram.h"
#include "texture.h"

#include <GL/glew.h>
#include <stb_image.h>
#include <glm/glm.hpp>

#include <cassert>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <vector>

namespace {
std::shared_ptr<ShaderProgram> CreateShaderProgram() {
    const std::string vertexPath =
        "Lessons/Transforms/shaders/shaderWithTexture.vert";
    const std::string fragmentPath =
        "Lessons/Transforms/shaders/shaderWithTexture.frag";

    return std::make_shared<ShaderProgram>(vertexPath, fragmentPath);
}

std::shared_ptr<BaseExcercise> make() {
    return std::make_shared<Ex_Transforms>();
}

std::shared_ptr<Mesh> CreateMesh() {
    const std::vector<VertexData_PosColorTexture> vertices = {
        // positions          // colors           // texture coords
        {{0.5f, 0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},    // UR
        {{0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},   // DR
        {{-0.5f, -0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},  // DL
        {{-0.5f, 0.5f}, {1.0f, 1.0f, 0.0f}, {0.0f, 1.0f}},   // UL
    };

    const std::vector<unsigned> indices = {
        0, 1, 3,  // first triangle
        1, 2, 3,  // second triangle
    };

    return std::make_shared<Mesh>(vertices, indices);
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

    m_shaderProgram->use();
    m_texture1->Bind();
    m_texture2->Bind();

    m_mesh->Draw();
}
