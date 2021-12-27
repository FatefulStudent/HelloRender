#ifndef EX_TEXTURES_H
#define EX_TEXTURES_H

#include "../../Lessons/BaseExcercise.h"

#include "Helper/VertexData.h"

#include <vector>

class ShaderProgram;

class Ex_Textures : public BaseExcercise {
public:
    Ex_Textures(){};
    virtual ~Ex_Textures(){};

    virtual void Initialize() override;
    virtual void Tick() override;
    virtual void Finalize() override;

private:
    ShaderProgram* m_shaderProgram = nullptr;
    std::vector<VertexData_PosColorTexture> m_vertices;

    unsigned int m_texture;
    unsigned int m_VAO;
    unsigned int m_VBO;
    unsigned int m_EBO;
};
#endif
