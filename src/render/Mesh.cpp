//
// Created by Daniel Laplana Gimeno on 22/4/25.
//

#include "Mesh.h"

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



void Mesh::Debug()
{

    std::cout << "Vertices: " << _numVertices << std::endl;
    for (int i = 0 ; i < _numVertices ; i++)
    {
        std::cout << "Vertex ["<< i << "] : " << _vertices[i] << std::endl;
    }

    std::cout << "Indices: " << _numIndices << std::endl;
    for (int i = 0 ; i < _numIndices ; i++)
    {
        std::cout << "Indices [" << i << "] : " << _indices[i] << std::endl;
    }
}