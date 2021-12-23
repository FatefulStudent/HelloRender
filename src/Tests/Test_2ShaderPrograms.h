#ifndef TEST_2_SHADER_PROGRAM_H
#define TEST_2_SHADER_PROGRAM_H

#include "BaseTest.h"

class ShaderProgram;

class Test_2ShaderPrograms : public BaseTest
{
public:
    Test_2ShaderPrograms() {};
    virtual ~Test_2ShaderPrograms() {};

    virtual void Initialize() override;
    virtual void Tick() override;
    virtual void Finalize() override;

private:
    ShaderProgram* m_shaderProgram1 = nullptr;
    ShaderProgram* m_shaderProgram2 = nullptr;

    unsigned int m_VAOs[2];
    unsigned int m_VBOs[2];
};
#endif
