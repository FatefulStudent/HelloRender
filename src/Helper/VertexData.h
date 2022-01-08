#ifndef VERTEX_DATA_H
#define VERTEX_DATA_H

#include <cstddef>

struct Vector3f {
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;

    static int GetNumberOfComponents() { return 3; }
};

struct Vector3u {
    unsigned x = 0;
    unsigned y = 0;
    unsigned z = 0;

    static int GetNumberOfComponents() { return 3; }
};

struct Vector2f {
    float x = 0.0f;
    float y = 0.0f;

    static int GetNumberOfComponents() { return 2; }
};

struct VertexData_PosColor {
    Vector3f Position{};
    Vector3f Color{};
};

struct VertexData_PosColorTexture {
    Vector2f Position{};
    Vector3f Color{};
    Vector2f Texture{};

    static int GetIndexForPosition() { return 0; }
    static int GetIndexForColor() { return 1; }
    static int GetIndexForTexture() { return 2; }

    static std::size_t GetSizeOfPosition() { return sizeof(Vector2f); }
    static std::size_t GetSizeOfColor() { return sizeof(Vector3f); }
    static std::size_t GetSizeOfTexture() { return sizeof(Vector2f); }

    static void* GetOffsetForPosition() { return (void*)0; }
    static void* GetOffsetForColor() { return (void*)(GetSizeOfPosition()); }
    static void* GetOffsetForTexture() {
        return (void*)(GetSizeOfPosition() + GetSizeOfColor());
    }

    static int GetNumberOfComponentsForPosition() {
        return Vector2f::GetNumberOfComponents();
    }
    static int GetNumberOfComponentsForColor() {
        return Vector3f::GetNumberOfComponents();
    }
    static int GetNumberOfComponentsForTexture() {
        return Vector2f::GetNumberOfComponents();
    }
};

#endif