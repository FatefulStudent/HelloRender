#ifndef EX_CAMERA_H
#define EX_CAMERA_H

#include "../../Lessons/BaseExcercise.h"
#include "Excercise.h"

#include "Helper/VertexData.h"

#include <memory>
#include <vector>

class ShaderProgram;
class Mesh;
class Texture;

class Ex_Camera : public BaseExcercise {
public:
    Ex_Camera(){};
    virtual ~Ex_Camera(){};

    virtual void Initialize(GLFWwindow* window) override;
    virtual void Tick() override;

private:
    std::shared_ptr<ShaderProgram> m_shaderProgram;
    std::shared_ptr<Mesh> m_mesh;
    std::shared_ptr<Texture> m_texture1;
    std::shared_ptr<Texture> m_texture2;
};

std::shared_ptr<BaseExcercise> make() {
    return std::make_shared<Ex_Camera>();
}
#endif
