
#include "VertexArray.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

VertexArray::VertexArray() {
	glGenVertexArrays(1, &_uid);
	glBindVertexArray(_uid);

	// _layoutBuffer = {};
}

VertexArray::~VertexArray() {
	glBindVertexArray(0);
	glDeleteVertexArrays(1, &_uid);
}

void VertexArray::Bind() {
	glBindVertexArray(_uid);
}

void VertexArray::Unbind() {
	glBindVertexArray(0);
}

void VertexArray::AddVertexBuffer(CometaRef<VertexBuffer> vertexBuffer)
{
	glBindVertexArray(_uid);

	vertexBuffer->Bind();
	_layoutBuffer.Bind();
	_vertexBuffers.push_back(vertexBuffer);
}

void VertexArray::AddIndexBuffer(CometaRef<IndexBuffer> indexBuffer)
{
	// Bind the VAO
	glBindVertexArray(_uid);

	indexBuffer->Bind();
	_indexBuffer = indexBuffer;
}

void VertexArray::CreateVertexBuffer(float* vertices, uint32_t size)
{
	// Bind the VAO
	glBindVertexArray(_uid);

	size_t currentSize = _vertexBuffers.size();
	// _vertexBuffers.resize( currentSize + 1);
	CometaRef<VertexBuffer> vbo = std::make_shared<VertexBuffer>(vertices, size);
	vbo->Bind();
	_vertexBuffers.push_back(vbo);

	// _vertexBuffers[currentSize]->Bind();
	// _vertexBuffers.back()->Bind();
	_layoutBuffer.Bind();
}
void VertexArray::CreateIndexBuffer(uint32_t* indices, uint32_t size)
{
	// Bind the VAO
	glBindVertexArray(_uid);

	_indexBuffer = std::make_shared<IndexBuffer>(indices, size);
	_indexBuffer->Bind();
}

CometaRef<VertexBuffer>& VertexArray::GetVertexBuffer(int index)
{
	return _vertexBuffers[index];
}