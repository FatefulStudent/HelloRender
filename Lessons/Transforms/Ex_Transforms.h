#ifndef EX_TRANSFORMS_H
#define EX_TRANSFORMS_H

#include "../../Lessons/BaseExcercise.h"
#include "Excercise.h"

#include "Helper/VertexData.h"

#include <memory>
#include <vector>

class ShaderProgram;
class Mesh;
class Texture;

class Ex_Transforms : public BaseExcercise {
public:
    Ex_Transforms(){};
    virtual ~Ex_Transforms(){};

    virtual void Initialize(GLFWwindow* window) override;
    virtual void Tick() override;

private:
    std::shared_ptr<ShaderProgram> m_shaderProgram;
    std::shared_ptr<Mesh> m_mesh;
    std::shared_ptr<Texture> m_texture1;
    std::shared_ptr<Texture> m_texture2;
};
#endif
