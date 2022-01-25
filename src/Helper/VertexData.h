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

struct VertexData_PosColorTexture {
    glm::vec2 Position{};
    glm::vec3 Color{};
    glm::vec2 Texture{};

    static int GetIndexForPosition() { return 0; }
    static int GetIndexForColor() { return 1; }
    static int GetIndexForTexture() { return 2; }

    static std::size_t GetSizeOfPosition() { return sizeof(glm::vec2); }
    static std::size_t GetSizeOfColor() { return sizeof(glm::vec3); }
    static std::size_t GetSizeOfTexture() { return sizeof(glm::vec2); }

    static void* GetOffsetForPosition() { return (void*)0; }
    static void* GetOffsetForColor() { return (void*)(GetSizeOfPosition()); }
    static void* GetOffsetForTexture() {
        return (void*)(GetSizeOfPosition() + GetSizeOfColor());
    }

    static int GetNumberOfComponentsForPosition() { return 2; }
    static int GetNumberOfComponentsForColor() { return 3; }
    static int GetNumberOfComponentsForTexture() { return 2; }
};

#endif