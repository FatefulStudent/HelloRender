#ifndef EX_TEXTURES_ADDITIONALS_H
#define EX_TEXTURES_ADDITIONALS_H

#include "../../Lessons/BaseExcercise.h"

#include "Helper/VertexData.h"

#include <memory>
#include <vector>

class ShaderProgram;
class Mesh;
class Texture;

class Ex_TexturesAdditionals : public BaseExcercise {
public:
    Ex_TexturesAdditionals(){};
    virtual ~Ex_TexturesAdditionals(){};

    virtual void Initialize(GLFWwindow* window) override;
    virtual void Tick() override;

private:
    static void key_callback(GLFWwindow* window,
                             int key,
                             int scancode,
                             int action,
                             int mods);
    std::shared_ptr<ShaderProgram> m_shaderProgram;
    std::shared_ptr<Mesh> m_mesh;
    std::shared_ptr<Texture> m_texture1;
    std::shared_ptr<Texture> m_texture2;
    static float m_alphaForTexturesBlend;
};
#endif
