#ifndef SHADER_INSTANCE_H
#define SHADER_INSTANCE_H

#include <map>

#include <GL/glew.h>

enum class EShaderType : uint8_t { Undefined, Vertex, Fragment };

class ShaderInstance {
private:
    static const std::map<EShaderType, int> ShaderTypeToGLShaderType;

    GLenum m_GLShaderType = 0;
    EShaderType m_shaderType = EShaderType::Undefined;
    unsigned m_GLShaderID = 0;

public:
    unsigned GetShaderID() const { return m_GLShaderID; }

    ShaderInstance(EShaderType shaderType, const char* shaderSource);
    ~ShaderInstance();
};

#endif
