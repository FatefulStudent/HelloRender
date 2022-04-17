#ifndef SHADER_COMPONENT_H
#define SHADER_COMPONENT_H

#include <string>
#include <vector>

#include "Component.h"
#include "Helper/MeshData.h"

class UShaderComponent : public UComponent {
public:
    UShaderComponent(const std::string& InVertexShaderPath,
                     const std::string& InFragmentShaderPath);
    virtual ~UShaderComponent(){};

    std::string VertexShaderPath;
    std::string FragmentShaderPath;

    glm::mat4 Model{};
    glm::mat4 View{};
    glm::mat4 Projection{};

    unsigned int ID = 0;
};

#endif