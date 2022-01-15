#ifndef EX_ADDITIONAL_TASKS_SHADERS_H
#define EX_ADDITIONAL_TASKS_SHADERS_H

#include "../../Lessons/BaseExcercise.h"

#include "Helper/VertexData.h"

#include <memory>
#include <vector>

class ShaderProgram;

class Ex_Additionals : public BaseExcercise {
public:
    Ex_Additionals(){};
    virtual ~Ex_Additionals(){};

    virtual void Initialize(GLFWwindow* window) override;
    virtual void Tick() override;

private:
    std::shared_ptr<ShaderProgram> m_shaderProgram;
    std::vector<Vector3f> m_vertices;

    unsigned int m_VAO;
    unsigned int m_VBO;
};
#endif
