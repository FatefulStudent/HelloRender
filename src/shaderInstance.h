#ifndef SHADER_INSTANCE_H
#define SHADER_INSTANCE_H

#include <GL/glew.h>

#include <map>

enum EShaderType { Undefined, Vertex, Fragment };

class ShaderInstance {
private:
    static const std::map<EShaderType, int> ShaderTypeToGLShaderType;
    static char infoLog[512];

    GLenum m_GLShaderType = NULL;
    EShaderType m_shaderType = EShaderType::Undefined;
    unsigned m_GLShaderID = NULL;

public:
    unsigned GetShaderID() const { return m_GLShaderID; }

    ShaderInstance(EShaderType shaderType, const char* shaderSource);
    ~ShaderInstance() {}
};

#endif
