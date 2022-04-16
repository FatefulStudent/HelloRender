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
std::string getExtensionOfFileName(const std::string& path) {
    size_t extensionStartIndex = path.rfind(".");
    if (extensionStartIndex == std::string::npos)
        return {};

    // Actually extension starts after the dot
    extensionStartIndex += 1;

    // if the dot was the last char in path then it has no extension
    if (extensionStartIndex == path.length())
        return {};

    const std::string extensionSubstring = path.substr(extensionStartIndex);
    return extensionSubstring;
}
};  // namespace ShaderInstanceLocal

const std::map<std::string, EShaderType>
    ShaderInstance::shaderPathExtensionToShaderType = {
        {std::string("vert"), EShaderType::Vertex},
        {std::string("frag"), EShaderType::Fragment},
};

const std::map<EShaderType, int> ShaderInstance::shaderTypeToGLShaderType = {
    {EShaderType::Undefined, NULL},
    {EShaderType::Vertex, GL_VERTEX_SHADER},
    {EShaderType::Fragment, GL_FRAGMENT_SHADER},
};

ShaderInstance::ShaderInstance(const std::string& shaderPath) {
    static char infoLog[512];
    m_shaderType = GetShaderTypeFromPath(shaderPath);

    if (m_shaderType == EShaderType::Undefined) {
        std::cerr << "ERROR::SHADER::INSTANCE ShaderType is Undefined.\n"
                  << std::endl;
        throw -1;
    }

    if (shaderPath.empty()) {
        std::cerr << "ERROR::SHADER::INSTANCE shaderPath is NULL.\n"
                  << std::endl;
        throw -1;
    }

    auto GLShaderTypeIter = shaderTypeToGLShaderType.find(m_shaderType);
    if (GLShaderTypeIter == shaderTypeToGLShaderType.end()) {
        std::cerr << "ERROR::SHADER::INSTANCE GLShaderType for ShaderType "
                  << static_cast<uint8_t>(m_shaderType)
                  << " is not found in ShaderTypeToGLShaderType Map.\n"
                  << std::endl;
        throw -1;
    }

    std::string shaderString = ShaderInstanceLocal::readFile(shaderPath);
    const char* shaderSource = shaderString.c_str();

    m_GLShaderType = GLShaderTypeIter->second;

    m_GLShaderID = glCreateShader(m_GLShaderType);
    glShaderSource(m_GLShaderID, 1, &shaderSource, NULL);
    glCompileShader(m_GLShaderID);

    int success;
    glGetShaderiv(m_GLShaderID, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(m_GLShaderID, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::INSTANCE::"
                  << static_cast<uint8_t>(m_shaderType)
                  << "::COMPILATION_FAILED\n"
                  << infoLog << std::endl;
        throw -1;
    }
}

ShaderInstance::~ShaderInstance() {
    glDeleteShader(GetShaderID());
}

EShaderType ShaderInstance::GetShaderTypeFromPath(
    const std::string& shaderPath) {
    const std::string extensionOfSource =
        ShaderInstanceLocal::getExtensionOfFileName(shaderPath);
    const auto pairWithExtension =
        shaderPathExtensionToShaderType.find(extensionOfSource);
    if (pairWithExtension == shaderPathExtensionToShaderType.end())
        return EShaderType::Undefined;
    else
        return pairWithExtension->second;
}
