//
// Created by Daniel Laplana Gimeno on 22/4/25.
//

#ifndef MESH_H
#define MESH_H

#include <vector>

#include "render/VertexArray.h"

class Mesh {
private:
    VertexArray _vao;

    std::vector<float> _vertices;
    uint32_t _numVertices = 0;

    std::vector<uint32_t> _indices;
    uint32_t _numIndices = 0;

public:
    Mesh();
    ~Mesh() = default;

    // ------------ CUSTOM MESH METHODS ------------

    void AddVertices(float* vertices, uint32_t numVertices);
    void AddIndices(uint32_t* indices, uint32_t numIndices);

    // Generates the VAO (VertexArray), VBO(VertexBuffer) and EBO(IndexBuffer)
    void Build();

    void Bind();
    void Unbind();

    void Draw();

    // ------------ DEBUG ------------

    void Debug();


    // ------------ GETTERS AND SETTERS ------------
    void SetLayoutBuffer(const LayoutBuffer& layoutBuffer){_vao.SetLayoutBuffer(layoutBuffer); }
    VertexArray& GetVertexArray() { return _vao; }
    [[nodiscard]] uint32_t GetNumVertices() const { return _numVertices; }
    [[nodiscard]] uint32_t GetNumIndices() const { return _numIndices; }
};



#endif //MESH_H
