#ifndef EX_SIMPLE_TRIANGLE_H
#define EX_SIMPLE_TRIANGLE_H

#include "../../Lessons/BaseExcercise.h"

#include "Helper/VertexData.h"

#include <vector>

class ShaderProgram;

class Ex_SimpleTriangle : public BaseExcercise {
public:
    Ex_SimpleTriangle(){};
    virtual ~Ex_SimpleTriangle(){};

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