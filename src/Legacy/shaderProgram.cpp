#include "shaderProgram.h"
#include "shaderInstance.h"

#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>

ShaderProgram::ShaderProgram(const std::string& vertexShaderPath,
                             const std::string& fragmentShaderPath) {
    ShaderInstance vertexShader(vertexShaderPath);
    assert(vertexShader.GetShaderType() == EShaderType::Vertex);

    ShaderInstance fragmentShader(fragmentShaderPath);
    assert(fragmentShader.GetShaderType() == EShaderType::Fragment);

    // shader Program
    m_id = glCreateProgram();
    glAttachShader(m_id, vertexShader.GetShaderID());
    glAttachShader(m_id, fragmentShader.GetShaderID());
    glLinkProgram(m_id);

    static int success;
    static char infoLog[512];

    glGetProgramiv(m_id, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(m_id, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
                  << infoLog << std::endl;
        throw -1;
    }
}

void ShaderProgram::use() {
    glUseProgram(m_id);
}

void ShaderProgram::setBool(const std::string& name, bool value) const {
    glUniform1i(glGetUniformLocation(m_id, name.c_str()), (int)value);
}

void ShaderProgram::setInt(const std::string& name, int value) const {
    glUniform1i(glGetUniformLocation(m_id, name.c_str()), value);
}

void ShaderProgram::setFloat(const std::string& name, float value) const {
    glUniform1f(glGetUniformLocation(m_id, name.c_str()), value);
}

void ShaderProgram::setVec3(const std::string& name,
                            const glm::vec3& value) const {
    GLuint location = glGetUniformLocation(m_id, name.c_str());

    glUniform3fv(location, 1, glm::value_ptr(value));
}

void ShaderProgram::setMatrix(const std::string& name,
                              const glm::mat4& value) const {
    unsigned int transformLoc = glGetUniformLocation(m_id, name.c_str());
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(value));
}
