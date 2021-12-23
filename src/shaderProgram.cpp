#include "shaderProgram.h"
#include "shaderInstance.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <cassert>

#include <GL/glew.h>


ShaderProgram::ShaderProgram(ShaderInstance* vertexShader, ShaderInstance* fragmentShader) {
    static int success;
    static char infoLog[512];

    assert(vertexShader);
    assert(fragmentShader);

    // shader Program
    m_id = glCreateProgram();
    glAttachShader(m_id, vertexShader->GetShaderID());
    glAttachShader(m_id, fragmentShader->GetShaderID());
    glLinkProgram(m_id);


    // delete the shaders as they're linked into our program now and no
    // longer necessary
    glDeleteShader(vertexShader->GetShaderID());
    glDeleteShader(fragmentShader->GetShaderID());

    delete vertexShader;
    delete fragmentShader;

    // print linking errors if any
    glGetProgramiv(m_id, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(m_id, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
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