#include "texture.h"
#include <GL/glew.h>
#include "stb_image.h"

#include <iostream>

Texture::Texture(const std::string& path, int textureUnitNumber) {
    m_textureUnitNumber = textureUnitNumber;
    glGenTextures(1, &m_Id);
    glBindTexture(GL_TEXTURE_2D, m_Id);
    // set the texture wrapping/filtering options (on the currently bound
    // texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                    GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load and generate the texture
    stbi_set_flip_vertically_on_load(true);
    int width, height, nrChannels;
    unsigned char* data =
        stbi_load(path.data(), &width, &height, &nrChannels, 0);
    if (data) {
        GLenum inputImageType = 0;
        if (nrChannels == 4)
            inputImageType = GL_RGBA;
        else if (nrChannels == 3)
            inputImageType = GL_RGB;
        else
            throw -1;

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
                     inputImageType, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cerr << "Failed to load texture at path \"" << path << "\""
                  << std::endl;
        throw -1;
    }
    stbi_image_free(data);
}

void Texture::Bind() {
    glActiveTexture(m_textureUnitNumber);
    glBindTexture(GL_TEXTURE_2D, m_Id);
}

Texture::~Texture() {
    // TODO: maybe clean up something here?
}
