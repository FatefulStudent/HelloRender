#include "ShaderComponent.h"

#include <utility>

UShaderComponent::UShaderComponent(std::string InVertexShaderPath,
                                   std::string InFragmentShaderPath)
    : Component(std::string("ShaderComponent")),
      VertexShaderPath(std::move(InVertexShaderPath)),
      FragmentShaderPath(std::move(InFragmentShaderPath)) {
    componentClass = EComponentClass::shaderComponent;
}
