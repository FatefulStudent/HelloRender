#ifndef EX_MODEL_LOADING_H
#define EX_MODEL_LOADING_H

#include "../../examples/BaseExcercise.h"
#include "Excercise.h"

#include "Helper/VertexData.h"

#include <memory>
#include <vector>
#include <string>

class Camera3d;
class ShaderProgram;
class Mesh;
class Texture;
class Model;

struct CelestalBody {
    std::string TexturePath = "";
    float Radius = 1.0f;
};

class ModelLoading : public BaseExcercise {
public:
    ModelLoading(){};
    virtual ~ModelLoading(){};

    virtual void Initialize(GLFWwindow* window) override;
    virtual void Tick(float deltaTime) override;
    virtual void Finalize() override;

private:
    std::vector<CelestalBody> m_CelestalBodies;
    std::shared_ptr<Camera3d> m_camera;
    std::shared_ptr<Model> m_model;

    std::shared_ptr<ShaderProgram> m_shaderProgramSun;
};

#endif
