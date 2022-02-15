#include "Ex_TexturesAdditionals.h"

#include "Helper/ApplicationHelper.h"
#include "Helper/VertexData.h"
#include "mesh.h"
#include "shaderInstance.h"
#include "shaderProgram.h"
#include "texture.h"

#include <GL/glew.h>
#include "stb_image.h"

#include <cassert>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <vector>

namespace {
std::shared_ptr<ShaderProgram> CreateShaderProgram() {
    const std::string vertexPath =
        "Lessons/Textures/shaders/shaderWithTexture.vert";
    const std::string fragmentPath =
        "Lessons/Textures/shaders/shaderWithTextureReversed.frag";

    return std::make_shared<ShaderProgram>(vertexPath, fragmentPath);
}

std::shared_ptr<Mesh> CreateMesh() {
    const std::vector<VertexData_PosColorTexture> vertices = {
        // positions          // colors           // texture coords
        {{0.5f, 0.5f}, {1.0f, 0.0f, 0.0f}, {2.0f, 2.0f}},    // UR
        {{0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {2.0f, 0.0f}},   // DR
        {{-0.5f, -0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},  // DL
        {{-0.5f, 0.5f}, {1.0f, 1.0f, 0.0f}, {0.0f, 2.0f}},   // UL
    };

    const std::vector<Vector3<unsigned>> indices = {
        {0, 1, 3},  // first triangle
        {1, 2, 3},  // second triangle
    };

    return std::make_shared<Mesh>(vertices, indices);
}
}  // namespace

float Ex_TexturesAdditionals::m_alphaForTexturesBlend = 0.2f;

void Ex_TexturesAdditionals::key_callback(GLFWwindow* window,
                                          int key,
                                          int scancode,
                                          int action,
                                          int mods) {
    if (key == GLFW_KEY_UP && action == GLFW_PRESS)
        m_alphaForTexturesBlend += 0.1f;
    else if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
        m_alphaForTexturesBlend -= 0.1f;

    m_alphaForTexturesBlend = fmin(fmax(m_alphaForTexturesBlend, 0.0f), 1.0f);
}

void Ex_TexturesAdditionals::Initialize(GLFWwindow* window) {
    BaseExcercise::Initialize(window);

    glfwSetKeyCallback(window, key_callback);

    m_texture1 =
        std::make_shared<Texture>("Resources/woodContainer.jpg", GL_TEXTURE0,
                                  GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);
    m_texture2 =
        std::make_shared<Texture>("Resources/awesomeFace.png", GL_TEXTURE1);

    m_mesh = CreateMesh();

    m_shaderProgram = CreateShaderProgram();
    m_shaderProgram->use();
    m_shaderProgram->setInt("Texture1", 0);
    m_shaderProgram->setInt("Texture2", 1);
}

void Ex_TexturesAdditionals::Tick() {
    BaseExcercise::Tick();

    m_shaderProgram->use();
    m_shaderProgram->setFloat("Alpha", m_alphaForTexturesBlend);
    m_texture1->Bind();
    m_texture2->Bind();

    m_mesh->Draw();
}
