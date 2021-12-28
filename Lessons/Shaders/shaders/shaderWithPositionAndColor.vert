#version 420 core
out vec3 Position;
out vec3 Color;
layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aColor;
void main() {
    gl_Position = vec4(aPosition, 1.0);
    Position = aPosition;
    Color = aColor;
}