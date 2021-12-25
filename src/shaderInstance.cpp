#include "shaderInstance.h"

#include <GL/glew.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

namespace ShaderInstanceLocal {
std::string readFile(const std::string& path) {
    std::ifstream input;
    input.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    std::stringstream sstr;
    try {
        input.open(path);
        sstr << input.rdbuf();
        input.close();
    } catch (std::ifstream::failure e) {
        std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: \"" << path
                  << "\":" << e.what() << std::endl;
        throw -1;
    }
    const std::string result = sstr.str();

    if (result.empty()) {
        std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: \"" << path
                  << std::endl;
        throw -1;
    }
    return result;
}
};  // namespace ShaderInstanceLocal

const std::map<EShaderType, int> ShaderInstance::ShaderTypeToGLShaderType =
    {
        {EShaderType::Undefined, NULL},
        {EShaderType::Vertex, GL_VERTEX_SHADER},
        {EShaderType::Fragment, GL_FRAGMENT_SHADER},
};

ShaderInstance::ShaderInstance(EShaderType shaderType,
                               const char* shaderPath) {
    static char infoLog[512];
    if (shaderType == EShaderType::Undefined) {
        std::cerr << "ERROR::SHADER::INSTANCE ShaderType is Undefined.\n"
                  << std::endl;
        throw -1;
    }

    if (!shaderPath) {
        std::cerr << "ERROR::SHADER::INSTANCE shaderPath is NULL.\n"
                  << std::endl;
        throw -1;
    }

    auto GLShaderTypeIter = ShaderTypeToGLShaderType.find(shaderType);
    if (GLShaderTypeIter == ShaderTypeToGLShaderType.end()) {
        std::cerr << "ERROR::SHADER::INSTANCE GLShaderType for ShaderType "
                  << static_cast<uint8_t>(shaderType)
                  << " is not found in ShaderTypeToGLShaderType Map.\n"
                  << std::endl;
        throw -1;
    }

    std::string shaderString = ShaderInstanceLocal::readFile(shaderPath);
    char* shaderSource = const_cast<char*>(shaderString.c_str());

    m_GLShaderType = GLShaderTypeIter->second;

    m_GLShaderID = glCreateShader(m_GLShaderType);
    glShaderSource(m_GLShaderID, 1, &shaderSource, NULL);
    glCompileShader(m_GLShaderID);

    int success;
    glGetShaderiv(m_GLShaderID, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(m_GLShaderID, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::INSTANCE::"
                  << static_cast<uint8_t>(shaderType)
                  << "::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
        throw -1;
    }
}

ShaderInstance::~ShaderInstance() {
    glDeleteShader(GetShaderID());
}
