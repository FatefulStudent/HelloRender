#version 420 core
in vec3 Position;
in vec3 Color;
out vec4 FragColor;
void main() {
    FragColor = vec4(Color, 1.0f);
}