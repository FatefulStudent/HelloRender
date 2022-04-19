#include "ShaderHelper.h"

#include "Components/ShaderComponent.h"

#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

void ShaderHelper::SetBool(UShaderComponent* ShaderComponent,
                           const std::string& name,
                           bool value) {
    if (!ShaderComponent) {
        assert(false);
        return;
    }

    glUniform1i(glGetUniformLocation(ShaderComponent->ShaderProgramID, name.c_str()),
                (int)value);
}

void ShaderHelper::SetInt(UShaderComponent* ShaderComponent,
                          const std::string& name,
                          int value) {
    if (!ShaderComponent) {
        assert(false);
        return;
    }

    glUniform1i(
        glGetUniformLocation(ShaderComponent->ShaderProgramID, name.c_str()),
                value);
}

void ShaderHelper::SetFloat(UShaderComponent* ShaderComponent,
                            const std::string& name,
                            float value) {
    if (!ShaderComponent) {
        assert(false);
        return;
    }

    glUniform1f(
        glGetUniformLocation(ShaderComponent->ShaderProgramID, name.c_str()),
                value);
}

void ShaderHelper::SetVec3(UShaderComponent* ShaderComponent,
                           const std::string& name,
                           const glm::vec3& value) {
    if (!ShaderComponent) {
        assert(false);
        return;
    }

    GLuint Location =
        glGetUniformLocation(ShaderComponent->ShaderProgramID, name.c_str());

    glUniform3fv(Location, 1, glm::value_ptr(value));
}

void ShaderHelper::SetMatrix(UShaderComponent* ShaderComponent,
                             const std::string& name,
                             const glm::mat4& value) {
    if (!ShaderComponent) {
        assert(false);
        return;
    }

    unsigned int transformLoc =
        glGetUniformLocation(ShaderComponent->ShaderProgramID, name.c_str());
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(value));
}
