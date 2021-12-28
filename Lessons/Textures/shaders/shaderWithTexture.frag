#version 420 core

in vec3 Color;
in vec2 TexCoord;
out vec4 FragColor;

uniform sampler2D Texture1;
uniform sampler2D Texture2;

void main() {
    FragColor = mix(texture(Texture1, TexCoord * 0.2),
                    texture(Texture2, TexCoord * 2), 0.2);
}
