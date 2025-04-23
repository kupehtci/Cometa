//
// Created by Daniel Laplana Gimeno on 22/4/25.
//

#include "Mesh.h"

// ------------ CONSTRUCTOR AND DESTRUCTOR ------------

Mesh::Mesh()
{
    // _vao = VertexArray();
}


// ------------ CUSTOM MESH METHODS ------------

void Mesh::AddVertices(float* vertices, uint32_t numVertices)
{
    _vertices.insert(_vertices.end(), vertices, vertices + numVertices);
    _numVertices += numVertices;
}

void Mesh::AddIndices(uint32_t* indices, uint32_t numIndices)
{
    _indices.insert(_indices.end(), indices, indices + numIndices);
    _numIndices += numIndices;
}

void Mesh::Build()
{
    _vao.Bind();
    //VertexBuffer vbo = VertexBuffer(this->_vertices.data(), _numVertices * sizeof(float));
    // IndexBuffer ebo = IndexBuffer(this->_indices.data(), _numIndices * sizeof(uint32_t));
    // _vao = VertexArray();
    _vao.CreateVertexBuffer(this->_vertices.data(), _numVertices * sizeof(float));
    _vao.CreateIndexBuffer(this->_indices.data(), _numIndices * sizeof(uint32_t));
    if (!_vao.GetLayoutBuffer().IsSet())
    {
        COMETA_WARNING("[Mesh] Cannot build mesh with unsettled LayoutBuffer");
    }
    _vao.GetLayoutBuffer().Bind();
    //_vao.AddVertexBuffer(vbo);
    //_vao.AddIndexBuffer(ebo);
    _vao.Bind();
}

void Mesh::Bind()
{
    _vao.Bind();
}

void Mesh::Unbind()
{
    _vao.Unbind();
}

void Mesh::Draw()
{
    glDrawElements(GL_TRIANGLES, static_cast<int>(_numIndices), GL_UNSIGNED_INT, 0);
}


void Mesh::Debug()
{

    std::cout << "Vertices: " << _numVertices << std::endl;
    // for (int i = 0 ; i < _numVertices ; i++)
    // {
    //     std::cout << "Vertex ["<< i << "] : " << _vertices[i] << std::endl;
    // }

    std::cout << "Indices: " << _numIndices << std::endl;
    // for (int i = 0 ; i < _numIndices ; i++)
    // {
    //     std::cout << "Indices [" << i << "] : " << _indices[i] << std::endl;
    // }

    std::cout << " --- MESH' BUFFERS --- " << std::endl;
    std::cout << "VertexArray uid: " << _vao.GetUid() << std::endl;

    std::cout << "VertexBuffer size: " << _vao.GetVertexBuffers().size() << std::endl;

    auto buffers = _vao.GetVertexBuffers();
    if (buffers.empty())
    {
        std::cout << "Vertex buffers are empty" << std::endl;
    }
    else
    {
        for (auto vbo : buffers)
        {
            std::cout << "\t VertexBuffer uid: " << vbo->GetUid() << std::endl;
        }
    }

    std::cout << "IndexBuffer uid: " << _vao.GetIndexBuffer()->GetUid() << std::endl;
}