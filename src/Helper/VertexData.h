#ifndef VERTEX_DATA_H
#define VERTEX_DATA_H

struct Vector3 {
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
};

struct Vector2 {
    float x = 0.0f;
    float y = 0.0f;
};

struct VertexData_PosColor {
    Vector3 Position{};
    Vector3 Color{};
};

struct VertexData_PosColorTexture {
    Vector2 Position{};
    Vector3 Color{};
    Vector2 Texture{};
};

#endif