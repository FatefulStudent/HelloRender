#ifndef VERTEX_DATA_H
#define VERTEX_DATA_H

#include <cstddef>

template <typename T>
struct Vector3 {
    T x;
    T y;
    T z;

    static int GetNumberOfComponents() { return 3; }
};

template <typename T>
struct Vector2 {
    T x;
    T y;

    static int GetNumberOfComponents() { return 2; }
};

struct VertexData_PosColor {
    Vector3<float> Position{};
    Vector3<float> Color{};
};

struct VertexData_PosColorTexture {
    Vector2<float> Position{};
    Vector3<float> Color{};
    Vector2<float> Texture{};

    static int GetIndexForPosition() { return 0; }
    static int GetIndexForColor() { return 1; }
    static int GetIndexForTexture() { return 2; }

    static std::size_t GetSizeOfPosition() { return sizeof(Vector2<float>); }
    static std::size_t GetSizeOfColor() { return sizeof(Vector3<float>); }
    static std::size_t GetSizeOfTexture() { return sizeof(Vector2<float>); }

    static void* GetOffsetForPosition() { return (void*)0; }
    static void* GetOffsetForColor() { return (void*)(GetSizeOfPosition()); }
    static void* GetOffsetForTexture() {
        return (void*)(GetSizeOfPosition() + GetSizeOfColor());
    }

    static int GetNumberOfComponentsForPosition() {
        return Vector2<float>::GetNumberOfComponents();
    }
    static int GetNumberOfComponentsForColor() {
        return Vector3<float>::GetNumberOfComponents();
    }
    static int GetNumberOfComponentsForTexture() {
        return Vector2<float>::GetNumberOfComponents();
    }
};

#endif