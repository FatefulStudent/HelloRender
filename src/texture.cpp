#include "texture.h"
#include <GL/glew.h>
#include "stb_image.h"

#include <iostream>

Texture::Texture(const std::string& path,
                 int textureUnitNumber,
                 int TextureWrappingS, /* = GL_REPEAT */
                 int TextureWrappingT, /* = GL_REPEAT */
                 int TextureMagFilter, /* = GL_LINEAR */
                 int TextureMinFilter  /* = GL_LINEAR_MIPMAP_LINEAR */
) {
    m_textureUnitNumber = textureUnitNumber;
    glGenTextures(1, &m_Id);
    glBindTexture(GL_TEXTURE_2D, m_Id);
    // set the texture wrapping/filtering options (on the currently bound
    // texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, TextureWrappingS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, TextureWrappingT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, TextureMagFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, TextureMinFilter);
    // load and generate the texture
    stbi_set_flip_vertically_on_load(true);
    int width, height, nrChannels;
    unsigned char* data =
        stbi_load(path.data(), &width, &height, &nrChannels, 0);
    if (data) {
        GLenum inputImageType = 0;
        if (nrChannels == 4) {
            inputImageType = GL_RGBA;
        } else if (nrChannels == 3) {
            inputImageType = GL_RGB;
        } else {
            stbi_image_free(data);
            throw -1;
        }

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
                     inputImageType, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        stbi_image_free(data);
    } else {
        std::cerr << "Failed to load texture at path \"" << path << "\""
                  << std::endl;
        throw -1;
    }
}

void Texture::Bind() {
    // glActiveTexture(m_textureUnitNumber);
    glBindTexture(GL_TEXTURE_2D, m_Id);
}

Texture::~Texture() {
    // TODO: maybe clean up something here?
}
