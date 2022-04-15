#ifndef EX_ARKANOID_H
#define EX_ARKANOID_H

#include "../../examples/BaseExcercise.h"
#include "Excercise.h"

#include "Helper/VertexData.h"

#include <memory>
#include <vector>
#include <string>

class Camera2d;
class ShaderProgram;
class Mesh;
class Texture;

struct CelestalBody {
    std::string TexturePath = "";
    float Radius = 1.0f;
};

class Arkanoid : public BaseExcercise {
public:
    Arkanoid(){};
    virtual ~Arkanoid(){};

    virtual void Initialize(GLFWwindow* window) override;
    virtual void Tick(float deltaTime) override;
    virtual void Finalize() override;

private:
    std::vector<CelestalBody> m_CelestalBodies;
    std::shared_ptr<Camera2d> m_camera;

    std::shared_ptr<ShaderProgram> m_shaderProgram;
    std::shared_ptr<ShaderProgram> m_shaderProgramSun;
    std::shared_ptr<Mesh> m_mesh;
    std::vector<std::shared_ptr<Texture>> m_textures;
};

std::shared_ptr<BaseExcercise> make() {
    return std::make_shared<Arkanoid>();
}
#endif
