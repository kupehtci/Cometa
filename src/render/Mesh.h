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

public:


    // ------------ CUSTOM MESH METHODS ------------

    void AddVertices(float* vertices)
    {
        _vertices.insert(_vertices.end(), vertices, vertices + 24);
    }


    VertexArray& GetVertexArray() { return _vao; }
};



#endif //MESH_H
