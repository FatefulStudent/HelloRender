#version 420 core
in vec3 Position;
uniform float BlueColor;
out vec4 FragColor;
void main() {
    FragColor = vec4(abs(Position.xy), BlueColor, 1.0f);
}