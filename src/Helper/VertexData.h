#ifndef VERTEX_DATA_H
#define VERTEX_DATA_H

#include <glm/glm.hpp>

#include <cstddef>

struct VertexData_PosColor {
    glm::vec3 Position{};
    glm::vec3 Color{};
};

struct VertexData_PosTexture {
    glm::vec3 Position{};
    glm::vec2 Texture{};

    static int GetIndexForPosition() { return 0; }
    static int GetIndexForTexture() { return 1; }

    static std::size_t GetSizeOfPosition() { return sizeof(glm::vec3); }
    static std::size_t GetSizeOfTexture() { return sizeof(glm::vec2); }

    static void* GetOffsetForPosition() { return (void*)0; }
    static void* GetOffsetForTexture() { return (void*)(GetSizeOfPosition()); }

    static int GetNumberOfComponentsForPosition() { return 3; }
    static int GetNumberOfComponentsForTexture() { return 2; }
};

#endif