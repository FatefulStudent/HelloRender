#ifndef SHADER_HELPER_H
#define SHADER_HELPER_H

#include "shaderInstance.h"
#include "shaderProgram.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace ShaderHelper {

ShaderInstance* CreateVertexShader() {
    const char* vertexShaderSource =
        "#version 420 core\n"
        "out vec3 Position;"
        "out vec3 Color;"
        "layout (location = 0) in vec3 aPosition;\n"
        "layout (location = 1) in vec3 aColor;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPosition, 1.0);\n"
        "   Position = aPosition;"
        "   Color = aColor;"
        "}\0";

    return new ShaderInstance(EShaderType::Vertex, vertexShaderSource);
}

ShaderInstance* CreateFragmentShader1() {
    const char* fragmentShader1Source =
        "#version 420 core\n"
        "in vec3 Position;"
        "in vec3 Color;"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "    FragColor = vec4(Color, 1.0f);\n"
        "}\0;";

    return new ShaderInstance(EShaderType::Fragment,
                              fragmentShader1Source);
}

ShaderInstance* CreateFragmentShader2() {
    const char* fragmentShader2Source =
        "#version 420 core\n"
        "in vec3 Position;"
        "uniform float BlueColor;"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "    FragColor = vec4(-Position.xy, BlueColor, 1.0f);\n"
        "}\0;";

    return new ShaderInstance(EShaderType::Fragment,
                              fragmentShader2Source);
}

ShaderProgram* CreateShaderProgram1() {
    ShaderInstance* vertexShaderInstance = CreateVertexShader();
    ShaderInstance* fragmentShaderInstance1 = CreateFragmentShader1();
    return new ShaderProgram(vertexShaderInstance,
                             fragmentShaderInstance1);
}

ShaderProgram* CreateShaderProgram2() {
    ShaderInstance* vertexShaderInstance = CreateVertexShader();
    ShaderInstance* fragmentShaderInstance1 = CreateFragmentShader2();
    return new ShaderProgram(vertexShaderInstance,
                             fragmentShaderInstance1);
}

}  // namespace ShaderHelper

#endif
