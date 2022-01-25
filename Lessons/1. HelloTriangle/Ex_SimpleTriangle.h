#ifndef EX_SIMPLE_TRIANGLE_H
#define EX_SIMPLE_TRIANGLE_H

#include "../../Lessons/BaseExcercise.h"

#include "Helper/VertexData.h"

#include <memory>
#include <vector>

class ShaderProgram;

class Ex_SimpleTriangle : public BaseExcercise {
public:
    Ex_SimpleTriangle(){};
    virtual ~Ex_SimpleTriangle(){};

    virtual void Initialize(GLFWwindow* window) override;
    virtual void Tick() override;

private:
    std::shared_ptr<ShaderProgram> m_shaderProgram;
    std::vector<Vector3<float>> m_vertices;

    unsigned int m_VAO;
    unsigned int m_VBO;
};
#endif
