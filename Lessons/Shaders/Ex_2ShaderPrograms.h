#ifndef TEST_2_SHADER_PROGRAM_H
#define TEST_2_SHADER_PROGRAM_H

#include "../../Lessons/BaseExcercise.h"

#include "Helper/VertexData.h"

#include <vector>

class ShaderProgram;

class Ex_2ShaderPrograms : public BaseExcercise {
public:
    Ex_2ShaderPrograms(){};
    virtual ~Ex_2ShaderPrograms(){};

    virtual void Initialize() override;
    virtual void Tick() override;
    virtual void Finalize() override;

private:
    ShaderProgram* m_shaderProgramWithColorInVertex = nullptr;
    ShaderProgram* m_shaderProgramWithUniformColor = nullptr;

    unsigned int m_VAOs[2];
    unsigned int m_VBOs[2];
    std::vector<VertexData> m_vertices1;
    std::vector<VertexData> m_vertices2;
};
#endif
