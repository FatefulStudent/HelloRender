#include "ShaderHelper.h"

#include "Components/ShaderComponent.h"

#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

void ShaderHelper::SetBool(unsigned ShaderProgramID,
                           const std::string& name,
                           bool value) {
    if (ShaderProgramID == 0) {
        assert(false);
        return;
    }

    glUniform1i(glGetUniformLocation(ShaderProgramID, name.c_str()),
                (int)value);
}

void ShaderHelper::SetInt(unsigned ShaderProgramID,
                          const std::string& name,
                          int value) {
    if (ShaderProgramID == 0) {
        assert(false);
        return;
    }

    glUniform1i(glGetUniformLocation(ShaderProgramID, name.c_str()), value);
}

void ShaderHelper::SetFloat(unsigned ShaderProgramID,
                            const std::string& name,
                            float value) {
    if (ShaderProgramID == 0) {
        assert(false);
        return;
    }

    glUniform1f(glGetUniformLocation(ShaderProgramID, name.c_str()), value);
}

void ShaderHelper::SetVec3(unsigned ShaderProgramID,
                           const std::string& name,
                           const glm::vec3& value) {
    if (ShaderProgramID == 0) {
        assert(false);
        return;
    }

    GLuint Location = glGetUniformLocation(ShaderProgramID, name.c_str());

    glUniform3fv(Location, 1, glm::value_ptr(value));
}

void ShaderHelper::SetMatrix(unsigned ShaderProgramID,
                             const std::string& name,
                             const glm::mat4& value) {
    if (ShaderProgramID == 0) {
        assert(false);
        return;
    }

    unsigned int transformLoc =
        glGetUniformLocation(ShaderProgramID, name.c_str());
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(value));
}
