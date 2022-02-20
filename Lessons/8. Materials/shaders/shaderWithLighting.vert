#version 420 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoord;

out vec3 Normal;
out vec3 FragPos;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

void main() {
    // note that we read the multiplication from right to left
    gl_Position = Projection * View * Model * vec4(aPos, 1.0);
    FragPos = vec3(Model * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(Model))) * aNormal;
}