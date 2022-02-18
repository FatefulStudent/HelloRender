#ifndef EX_CAMERA_H
#define EX_CAMERA_H

#include "../../Lessons/BaseExcercise.h"
#include "Excercise.h"

#include "Helper/VertexData.h"

#include <memory>
#include <vector>

class Camera;
class ShaderProgram;
class Mesh;
class Texture;

struct CelestalBody {
    std::string TexturePath = "";
    float DistanceFromOrigin = 0.0f;
    float Radius = 1.0f;
};

class Ex_SolarSystemProject : public BaseExcercise {
public:
    Ex_SolarSystemProject(){};
    virtual ~Ex_SolarSystemProject(){};

    virtual void Initialize(GLFWwindow* window) override;
    virtual void Tick(float deltaTime) override;

private:
    std::vector<CelestalBody> m_CelestalBodies;
    std::shared_ptr<Camera> m_camera;

    std::shared_ptr<ShaderProgram> m_shaderProgram;
    std::shared_ptr<ShaderProgram> m_shaderProgramSun;
    std::shared_ptr<Mesh> m_mesh;
    std::vector<std::shared_ptr<Texture>> m_textures;
};

std::shared_ptr<BaseExcercise> make() {
    return std::make_shared<Ex_SolarSystemProject>();
}
#endif
