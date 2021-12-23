#ifndef SHADER_INSTANCE_H
#define SHADER_INSTANCE_H

#include <map>

#include <GL/glew.h>

enum EShaderType { Undefined, Vertex, Fragment };

class ShaderInstance {
private:
    static const std::map<EShaderType, int> ShaderTypeToGLShaderType;

    GLenum m_GLShaderType = NULL;
    EShaderType m_shaderType = EShaderType::Undefined;
    unsigned m_GLShaderID = NULL;

public:
    unsigned GetShaderID() const { return m_GLShaderID; }

    ShaderInstance(EShaderType shaderType, const char* shaderSource);
    ~ShaderInstance() {}
};

#endif
