#version 420 core
out vec3 Position;
uniform float XOffset;
layout(location = 0) in vec3 aPos;

void main() {
    gl_Position = vec4(-(aPos.x + XOffset), -aPos.yz, 1.0);
    Position = gl_Position.xyz;
};
