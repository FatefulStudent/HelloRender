#include "Mesh.h"
#include "ShaderProgram.h"

#include "Helper/ShaderHelper.h"

Mesh::Mesh(const std::vector<FVertex>& vertices,
           const std::vector<unsigned int>& indices,
           const std::vector<FTexture>& textures) {
    this->Vertices = vertices;
    this->Indices = indices;
    this->Textures = textures;

    // now that we have all the required data, set the vertex buffers and
    // its attribute pointers.
    SetupMesh();
}

void Mesh::Draw(UShaderComponent* ShaderComponent) {
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    for (unsigned int i = 0; i < Textures.size(); i++) {
        glActiveTexture(GL_TEXTURE0 +
                        i);  // activate proper texture unit before binding
        // retrieve texture number (the N in diffuse_textureN)
        std::string number;
        std::string name = Textures[i].Type;
        if (name == "texture_diffuse")
            number = std::to_string(diffuseNr++);
        else if (name == "texture_specular")
            number = std::to_string(specularNr++);

        if (ShaderComponent)
            ShaderHelper::SetFloat(ShaderComponent, ("material." + name + number).c_str(), i);
        glBindTexture(GL_TEXTURE_2D, Textures[i].ID);
    }
    glActiveTexture(GL_TEXTURE0);

    // draw mesh
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, Indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Mesh::SetupMesh() {
    // create buffers/arrays
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    // load data into vertex buffers
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // A great thing about structs is that their memory layout is
    // sequential for all its items. The effect is that we can simply pass
    // a pointer to the struct and it translates perfectly to a glm::vec3/2
    // array which again translates to 3/2 floats which translates to a
    // byte array.
    glBufferData(GL_ARRAY_BUFFER, Vertices.size() * sizeof(FVertex),
                 &Vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 Indices.size() * sizeof(unsigned int), &Indices[0],
                 GL_STATIC_DRAW);

    // set the vertex attribute pointers
    // vertex Positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(FVertex), (void*)0);
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(FVertex),
                          (void*)offsetof(FVertex, Normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(FVertex),
                          (void*)offsetof(FVertex, TexCoords));
    glBindVertexArray(0);
}
