#ifndef SHADER_HELPER_H
#define SHADER_HELPER_H

#include <glm/glm.hpp>
#include <string>

namespace ShaderHelper {
void SetVec3(unsigned ShaderProgramID,
             const std::string& name,
             const glm::vec3& value);
void SetBool(unsigned ShaderProgramID, const std::string& name, bool value);
void SetInt(unsigned ShaderProgramID, const std::string& name, int value);
void SetFloat(unsigned ShaderProgramID, const std::string& name, float value);
void SetMatrix(unsigned ShaderProgramID,
               const std::string& name,
               const glm::mat4& value);
}  // namespace ShaderHelper

#endif  // !SHADER_HELPER_H
