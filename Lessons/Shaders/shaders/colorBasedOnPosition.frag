#version 420 core
in vec3 Position;
out vec4 FragColor;

void main() {
    FragColor = vec4(Position, 1.0f) * vec4(1.0f, 0.5f, 0.2f, 1.0f);
}
