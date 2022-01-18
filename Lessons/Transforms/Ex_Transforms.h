#ifndef EX_TRANSFORMS_H
#define EX_TRANSFORMS_H

#include "../../Lessons/BaseExcercise.h"

#include "Helper/VertexData.h"

#include <memory>
#include <vector>

class ShaderProgram;

class Ex_Transforms : public BaseExcercise {
public:
    Ex_Transforms(){};
    virtual ~Ex_Transforms(){};

    virtual void Initialize(GLFWwindow* window) override;
    virtual void Tick() override;

private:
    std::shared_ptr<ShaderProgram> m_shaderProgram;
    std::vector<Vector3<float>> m_vertices;

    unsigned int m_VAO;
    unsigned int m_VBO;
};
#endif
