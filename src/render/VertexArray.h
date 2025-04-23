#pragma once

#include <vector>
#include "Buffer.h"
#include "render/LayoutBuffer.h"

#include "core/CometaBase.h"

class VertexArray : public Buffer {

private: 
	std::vector<CometaRef<VertexBuffer>> _vertexBuffers;
	CometaRef<IndexBuffer> _indexBuffer;
	LayoutBuffer _layoutBuffer;
public: 
	VertexArray();
	~VertexArray() override;

	void Bind() override;
	void Unbind() override;

	void AddVertexBuffer(CometaRef<VertexBuffer> vertexBuffer);
	void AddIndexBuffer(CometaRef<IndexBuffer> indexBuffer);

	void CreateVertexBuffer(float* vertices, uint32_t size);
	void CreateIndexBuffer(uint32_t* indices, uint32_t size);

	CometaRef<VertexBuffer>& GetVertexBuffer(int index);

	// ------------ LAYOUT BUFFER METHODS ------------
	void SetLayoutBuffer(const LayoutBuffer& layout_buffer)
	{
		_layoutBuffer = layout_buffer;
		_layoutBuffer.Build();
	}
	LayoutBuffer GetLayoutBuffer() {return _layoutBuffer; }

	std::vector<CometaRef<VertexBuffer>>& GetVertexBuffers() { return _vertexBuffers; }
	CometaRef<IndexBuffer>& GetIndexBuffer() { return _indexBuffer; }
};