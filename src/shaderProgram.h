#ifndef SHADER_PROGRAM_H
#define SHADER_PROGRAM_H

#include <string>

class ShaderInstance;

class ShaderProgram {
public:
    unsigned int m_id;

    ShaderProgram(const std::string& vertexShaderSource,
                  const std::string& fragmentShaderSource);
    ~ShaderProgram() {}

    void use();

    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
};

#endif