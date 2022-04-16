#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>  // holds all OpenGL type declarations

#include <glm/glm.hpp>

#include <string>
#include <vector>

class ShaderProgram;

struct Vertex {
    // position
    glm::vec3 Position;
    // normal
    glm::vec3 Normal;
    // texCoords
    glm::vec2 TexCoords;
};

struct Texture {
    unsigned int id = 0;
    std::string type{};
    std::string path{};
};

class Mesh {
public:
    // mesh Data
    std::vector<Vertex> Vertices;
    std::vector<unsigned int> Indices;
    std::vector<Texture> Textures;
    unsigned int VAO;

    // constructor
    Mesh(const std::vector<Vertex>& vertices,
         const std::vector<unsigned int>& indices,
         const std::vector<Texture>& textures);

    void Draw(ShaderProgram* shader);

private:
    // render data
    unsigned int VBO, EBO;

    // initializes all the buffer objects/arrays
    void SetupMesh();
};

#endif