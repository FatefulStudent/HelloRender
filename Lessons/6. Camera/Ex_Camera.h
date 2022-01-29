#ifndef EX_CAMERA_H
#define EX_CAMERA_H

#include "../../Lessons/BaseExcercise.h"
#include "Excercise.h"

#include "Helper/VertexData.h"

#include <memory>
#include <vector>

class ShaderProgram;
class Mesh;
class Texture;

class Ex_Camera : public BaseExcercise {
public:
    Ex_Camera(){};
    virtual ~Ex_Camera(){};

    virtual void Initialize(GLFWwindow* window) override;
    virtual void ProcessInput(float deltaTime) override;
    virtual void Tick(float deltaTime) override;

private:
    static void ScrollCallback(GLFWwindow* window,
                               double xoffset,
                               double yoffset);
    static float fov;

    std::shared_ptr<ShaderProgram> m_shaderProgram;
    std::shared_ptr<Mesh> m_mesh;
    std::shared_ptr<Texture> m_texture1;
    std::shared_ptr<Texture> m_texture2;

    glm::vec3 m_cameraPos = {0.0f, 0.0f, 0.0f};
    glm::vec3 m_cameraUp = {0.0f, 1.0f, 0.0f};
    glm::vec3 m_cameraFront = {0.0f, 0.0f, -1.0f};
    glm::vec2 m_cachedCursorPos = {0.0f, 0.0f};
    float m_yaw = -90.0f;
    float m_pitch = 0.0f;
};

std::shared_ptr<BaseExcercise> make() {
    return std::make_shared<Ex_Camera>();
}
#endif
