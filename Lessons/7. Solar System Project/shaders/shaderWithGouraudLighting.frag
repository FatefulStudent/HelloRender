#version 420 core

in vec2 TexCoord;
in vec3 FragColorByLighting;
out vec4 FragColor;

uniform sampler2D Texture;

void main() {
    vec4 TextureColor = texture(Texture, TexCoord);

    FragColor = vec4(FragColorByLighting, 1.0) * TextureColor;
}
