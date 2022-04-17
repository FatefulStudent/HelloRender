#include "ShaderData.h"

#include <GL/glew.h>

const std::map<std::string, EShaderType>
    FShaderData::FileExtensionToShaderType = {
        {std::string("vert"), EShaderType::Vertex},
        {std::string("frag"), EShaderType::Fragment},
};

const std::map<EShaderType, int> FShaderData::ShaderTypeToGLShaderType = {
    {EShaderType::Undefined, NULL},
    {EShaderType::Vertex, GL_VERTEX_SHADER},
    {EShaderType::Fragment, GL_FRAGMENT_SHADER},
};

FShaderData::~FShaderData() {
    glDeleteShader(ID);
}
