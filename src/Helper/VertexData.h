#ifndef VERTEX_DATA_H
#define VERTEX_DATA_H

struct Vector3 {
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
};

struct VertexData {
    Vector3 Location{};
    Vector3 Color{};
};

#endif