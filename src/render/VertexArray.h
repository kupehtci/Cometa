#pragma once

#include <vector>
#include "Buffer.h"

class VertexArray : public Buffer {

private: 
	std::vector<VertexBuffer> _vertexBuffers;
	IndexBuffer _indexBuffer;
public: 
	VertexArray();
	~VertexArray() override;

	void Bind() override;
	void Unbind() override;

	void AddVertexBuffer(VertexBuffer& vertexBuffer);
	void AddIndexBuffer(IndexBuffer& indexBuffer);

	std::vector<VertexBuffer>& GetVertexBuffers() { return _vertexBuffers; }
	IndexBuffer& GetIndexBuffer() { return _indexBuffer; }
};