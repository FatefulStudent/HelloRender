#ifndef TEST_2_SIMPLE_TRIANGLE_H
#define TEST_2_SIMPLE_TRIANGLE_H

#include "BaseTest.h"

#include "Helper/VertexData.h"

#include <vector>

class ShaderProgram;

class Test_SimpleTriangle : public BaseTest {
public:
    Test_SimpleTriangle(){};
    virtual ~Test_SimpleTriangle(){};

    virtual void Initialize() override;
    virtual void Tick() override;
    virtual void Finalize() override;

private:
    ShaderProgram* m_shaderProgram = nullptr;
    std::vector<Vector3> m_vertices;

    unsigned int m_VAO;
    unsigned int m_VBO;
};
#endif
