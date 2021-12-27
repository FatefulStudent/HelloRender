#include "shaderProgram.h"
#include "shaderInstance.h"

#include <GL/glew.h>

#include <cassert>
#include <fstream>
#include <iostream>
#include <sstream>

ShaderProgram::ShaderProgram(const char* vertexShaderPath,
                             const char* fragmentShaderPath) {
    ShaderInstance vertexShader(EShaderType::Vertex, vertexShaderPath);
    ShaderInstance fragmentShader(EShaderType::Fragment, fragmentShaderPath);

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