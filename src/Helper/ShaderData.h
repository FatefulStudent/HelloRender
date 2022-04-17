#ifndef SHADER_DATA_H
#define SHADER_DATA_H

#include <map>
#include <string>

#include <GL/glew.h>

enum class EShaderType : uint8_t { Undefined, Vertex, Fragment };

struct FShaderData {
    std::string ShaderPath{};
    GLenum GLShaderType = 0;
    EShaderType ShaderType = EShaderType::Undefined;
    unsigned ID = 0;

    ~FShaderData();
    
    static const std::map<std::string, EShaderType> FileExtensionToShaderType;
    static const std::map<EShaderType, int> ShaderTypeToGLShaderType;
};

#endif
