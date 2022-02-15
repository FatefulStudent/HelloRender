#ifndef TEST_2_SHADER_PROGRAM_H
#define TEST_2_SHADER_PROGRAM_H

#include "../../Lessons/BaseExcercise.h"

#include "Helper/VertexData.h"

#include <memory>
#include <vector>

class ShaderProgram;

class Ex_2ShaderPrograms : public BaseExcercise {
public:
    Ex_2ShaderPrograms(){};
    virtual ~Ex_2ShaderPrograms(){};

    virtual void Initialize(GLFWwindow* window) override;
    virtual void Tick() override;

private:
    std::shared_ptr<ShaderProgram> m_shaderProgramWithColorInVertex;
    std::shared_ptr<ShaderProgram> m_shaderProgramWithUniformColor;

    unsigned int m_VAOs[2];
    unsigned int m_VBOs[2];
    std::vector<VertexData_PosColor> m_vertices1;
    std::vector<VertexData_PosColor> m_vertices2;
};
#endif
