#version 420 core

in vec2 TexCoord;
out vec4 FragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;

uniform sampler2D Texture;

void main() {
    // FragColor = texture(Texture, TexCoord);
    FragColor =
        vec4(lightColor * objectColor, 1.0) * texture(Texture, TexCoord);
}
