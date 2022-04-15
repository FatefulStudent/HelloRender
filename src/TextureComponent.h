#ifndef TEXTURE_COMPONENT_H
#define TEXTURE_COMPONENT_H

#include <string>
#include <vector>

#include "Component.h"
#include "Helper/VertexData.h"

class UTextureComponent : public UComponent {
public:
    UTextureComponent(std::string&& InPath,
                      int InTextureUnitNumber,
                      int InTextureWrappingS = GL_REPEAT,
                      int InTextureWrappingT = GL_REPEAT,
                      int InTextureMagFilter = GL_LINEAR,
                      int InTextureMinFilter = GL_LINEAR_MIPMAP_LINEAR);

    unsigned int ID = 0;

    std::string Path{};
    int TextureUnitNumber = 0;
    int TextureWrappingS = GL_REPEAT;
    int TextureWrappingT = GL_REPEAT;
    int TextureMagFilter = GL_LINEAR;
    int TextureMinFilter = GL_LINEAR_MIPMAP_LINEAR;
};

#endif