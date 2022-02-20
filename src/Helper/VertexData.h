#ifndef VERTEX_DATA_H
#define VERTEX_DATA_H

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <cstddef>

struct VertexData_PosColor {
    glm::vec3 Position{};
    glm::vec3 Color{};
};

struct VertexData_PosNormalTexture {
    glm::vec3 Position{};
    glm::vec3 Normal{};
    glm::vec2 Texture{};

    static int GetIndexForPosition() { return 0; }
    static int GetIndexForNormal() { return 1; }
    static int GetIndexForTexture() { return 2; }

    static std::size_t GetSizeOfPosition() { return sizeof(glm::vec3); }
    static std::size_t GetSizeOfNormal() { return sizeof(glm::vec3); }
    static std::size_t GetSizeOfTexture() { return sizeof(glm::vec2); }

    static void* GetOffsetForPosition() { return (void*)0; }
    static void* GetOffsetForNormal() { return (void*)(GetSizeOfPosition()); }
    static void* GetOffsetForTexture() {
        return (void*)(GetSizeOfPosition() + GetSizeOfNormal());
    }

    static int GetNumberOfComponentsForPosition() { return 3; }
    static int GetNumberOfComponentsForNormal() { return 3; }
    static int GetNumberOfComponentsForTexture() { return 2; }
};

struct Index {
    GLuint indices[3];
};

#endif