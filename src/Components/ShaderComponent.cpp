#include "ShaderComponent.h"

#include <utility>

UShaderComponent::UShaderComponent(std::string InVertexShaderPath,
                                   std::string InFragmentShaderPath)
    : UComponent(std::string("ShaderComponent")),
      VertexShaderPath(std::move(InVertexShaderPath)),
      FragmentShaderPath(std::move(InFragmentShaderPath)) {
    ComponentClass = EComponentClass::UShaderComponent;
}
