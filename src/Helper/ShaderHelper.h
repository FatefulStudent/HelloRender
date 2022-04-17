#ifndef SHADER_HELPER_H
#define SHADER_HELPER_H

#include <glm/glm.hpp>
#include <string>

class UShaderComponent;

namespace ShaderHelper {
void SetVec3(UShaderComponent* ShaderComponent,
             const std::string& name,
             const glm::vec3& value);
void SetBool(UShaderComponent* ShaderComponent,
             const std::string& name,
             bool value);
void SetInt(UShaderComponent* ShaderComponent,
            const std::string& name,
            int value);
void SetFloat(UShaderComponent* ShaderComponent,
              const std::string& name,
              float value);
void SetMatrix(UShaderComponent* ShaderComponent,
               const std::string& name,
               const glm::mat4& value);
}  // namespace ShaderHelper

#endif  // !SHADER_HELPER_H
