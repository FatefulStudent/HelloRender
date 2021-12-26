#ifndef EX_ADDITIONAL_TASKS_SHADERS_H
#define EX_ADDITIONAL_TASKS_SHADERS_H

#include "../../Lessons/BaseExcercise.h"

#include "Helper/VertexData.h"

#include <vector>

class ShaderProgram;

class Ex_Additionals : public BaseExcercise {
public:
    Ex_Additionals(){};
    virtual ~Ex_Additionals(){};

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
