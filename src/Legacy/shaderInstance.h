#ifndef SHADER_INSTANCE_H
#define SHADER_INSTANCE_H

#include <map>
#include <string>

#include <GL/glew.h>

enum class EShaderType : uint8_t { Undefined, Vertex, Fragment };

class ShaderInstance {
private:
    static const std::map<std::string, EShaderType>
        shaderPathExtensionToShaderType;
    static const std::map<EShaderType, int> shaderTypeToGLShaderType;

    GLenum m_GLShaderType = 0;
    EShaderType m_shaderType = EShaderType::Undefined;
    unsigned m_GLShaderID = 0;

public:
    unsigned GetShaderID() const { return m_GLShaderID; }
    EShaderType GetShaderType() const { return m_shaderType; }

    ShaderInstance(const std::string& shaderPath);
    ~ShaderInstance();

private:
    static EShaderType GetShaderTypeFromPath(const std::string& shaderPath);
};

#endif
