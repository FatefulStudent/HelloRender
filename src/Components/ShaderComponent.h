#ifndef SHADER_COMPONENT_H
#define SHADER_COMPONENT_H

#include "Component.h"

#include <glm/matrix.hpp>

#include <string>

class UShaderComponent : public UComponent {
public:
    UShaderComponent(std::string InVertexShaderPath,
                     std::string InFragmentShaderPath);
    virtual ~UShaderComponent() = default;

    std::string VertexShaderPath{};
    std::string FragmentShaderPath{};

    glm::mat4 View{};
    glm::mat4 Projection{};

    unsigned ShaderProgramID = 0;
};

#endif