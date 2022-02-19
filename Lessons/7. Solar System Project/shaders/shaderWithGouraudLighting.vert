#version 420 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoord;

out vec2 TexCoord;
out vec3 FragColorByLighting;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

uniform float ambientStrength;
uniform float specularStrength;
uniform float diffuseStrength;
uniform int shininess;
uniform int index;

void main() {
    // note that we read the multiplication from right to left
    gl_Position = Projection * View * Model * vec4(aPos, 1.0);
    TexCoord = vec2(aTexCoord.x, aTexCoord.y);

    vec3 VertexPos = vec3(Model * vec4(aPos, 1.0));
    vec3 VertexNormal = mat3(transpose(inverse(Model))) * aNormal;

    vec3 ambient = ambientStrength * lightColor;

    vec3 norm = normalize(VertexNormal);
    vec3 lightDir = normalize(lightPos - VertexPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diffuseStrength * diff * lightColor;

    vec3 viewDir = normalize(viewPos - VertexPos);
    vec3 reflectDir = reflect(-lightDir, norm);

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    vec3 specular = specularStrength * spec * lightColor;

    // float DistanceBasedMultiplier = 1.0 / (index * index);

    FragColorByLighting = (ambient + diffuse + specular) *
                          objectColor;  // * DistanceBasedMultiplier;
}