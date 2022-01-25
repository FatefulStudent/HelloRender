#version 420 core
in vec3 Position;
out vec4 FragColor;

void main() {
    FragColor = vec4(abs(Position), 1.0f);
}
