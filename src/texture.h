#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>

#include <string>

class Texture {
private:
    unsigned int m_Id = 0;
    int m_textureUnitNumber = 0;

public:
    Texture(const std::string& path,
            int textureUnitNumber,
            int TextureWrappingS = GL_REPEAT,
            int TextureWrappingT = GL_REPEAT,
            int TextureMagFilter = GL_LINEAR,
            int TextureMinFilter = GL_LINEAR_MIPMAP_LINEAR);
    ~Texture();

    void Bind();
};
#endif
