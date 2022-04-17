#include "ShaderComponent.h"

UShaderComponent::UShaderComponent(const std::string& InVertexShaderPath,
                                   const std::string& InFragmentShaderPath)
    : VertexShaderPath(InVertexShaderPath),
      FragmentShaderPath(InFragmentShaderPath){}
