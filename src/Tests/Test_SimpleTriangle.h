#ifndef TEST_2_SHADER_PROGRAM_H
#define TEST_2_SHADER_PROGRAM_H

#include "BaseTest.h"

class ShaderProgram;

class Test_SimpleTriangle : public BaseTest
{
public:
    Test_SimpleTriangle() {};
    virtual ~Test_SimpleTriangle() {};

    virtual void Initialize() override;
    virtual void Tick() override;
    virtual void Finalize() override;

private:
    ShaderProgram* m_shaderProgram = nullptr;

    unsigned int m_VAO;
    unsigned int m_VBO;
};
#endif
