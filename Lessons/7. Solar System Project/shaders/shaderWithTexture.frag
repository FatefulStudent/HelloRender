#version 420 core

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;
out vec4 FragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

uniform float ambientStrength;
uniform float specularStrength;

uniform sampler2D Texture;

void main() {
    vec4 TextureColor = texture(Texture, TexCoord);
    vec3 ambient = ambientStrength * lightColor;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = vec3(0);
    if (TextureColor.b > 0.3 && TextureColor.r < 0.5 && TextureColor.g < 0.5)
        specular = specularStrength * spec * lightColor;

    vec3 result = (ambient + diffuse + specular) * objectColor;

    FragColor = vec4(result, 1.0) * TextureColor;
}
