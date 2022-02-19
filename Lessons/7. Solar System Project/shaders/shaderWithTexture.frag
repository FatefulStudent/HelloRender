#version 420 core

in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;
out vec4 FragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform mat4 View;

uniform float ambientStrength;
uniform float specularStrength;
uniform float diffuseStrength;
uniform int shininess;
uniform int index;

uniform sampler2D Texture;

void main() {
    vec4 TextureColor = texture(Texture, TexCoord);
    vec3 ambient = ambientStrength * lightColor;

    vec3 norm = normalize(vec3(View * vec4(Normal, 0.0)));
    vec3 lightDirection = lightPos - FragPos;
    vec3 lightDir = normalize(vec3(View * vec4(lightDirection, 0.0)));

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diffuseStrength * diff * lightColor;

    vec3 viewDir = normalize(vec3(View * vec4(viewPos - FragPos, 0.0)));
    vec3 reflectDir = reflect(-lightDir, norm);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    vec3 specular = specularStrength * spec * lightColor;

    float DistanceBasedMultiplier = 1.0;  // / (index * index);

    vec3 result =
        (ambient + diffuse + specular) * objectColor * DistanceBasedMultiplier;

    FragColor = vec4(result, 1.0) * TextureColor;
}
