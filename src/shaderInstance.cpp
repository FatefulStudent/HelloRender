#include "shaderInstance.h"

#include <GL/glew.h>

#include <iostream>

const std::map<EShaderType, int> ShaderInstance::ShaderTypeToGLShaderType =
    {
        {Undefined, NULL},
        {Vertex, GL_VERTEX_SHADER},
        {Fragment, GL_FRAGMENT_SHADER},
};

ShaderInstance::ShaderInstance(EShaderType shaderType,
                               const char* shaderSource) {
    if (shaderType == EShaderType::Undefined) {
        std::cerr << "ERROR::SHADER::INSTANCE ShaderType is Undefined.\n"
                  << std::endl;
        throw - 1;
    }

    if (!shaderSource) {
        std::cerr << "ERROR::SHADER::INSTANCE  shaderSource is NULL.\n"
                  << std::endl;
        throw - 1;
    }

    auto GLShaderTypeIter = ShaderTypeToGLShaderType.find(shaderType);
    if (GLShaderTypeIter == ShaderTypeToGLShaderType.end()) {
        std::cerr << "ERROR::SHADER::INSTANCE GLShaderType for ShaderType "
                  << shaderType
                  << " is not found in ShaderTypeToGLShaderType Map.\n"
                  << std::endl;
        throw - 1;
    }

    m_GLShaderType = GLShaderTypeIter->second;

    m_GLShaderID = glCreateShader(m_GLShaderType);
    glShaderSource(m_GLShaderID, 1, &shaderSource, NULL);
    glCompileShader(m_GLShaderID);

    int success;
    glGetShaderiv(m_GLShaderID, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(m_GLShaderID, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::INSTANCE::" << shaderType
                  << "::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
        throw - 1;
    }
}