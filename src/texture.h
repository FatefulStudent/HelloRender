#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>

class Texture {
private:
    unsigned int m_Id = 0;
    int m_textureUnitNumber = 0;

public:
    Texture(const std::string& path, int textureUnitNumber);
    ~Texture();

    void Bind();
};
#endif
