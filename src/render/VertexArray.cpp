
#include "VertexArray.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

VertexArray::VertexArray() {
	glGenVertexArrays(1, &_uid);
	glBindVertexArray(_uid);
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

void VertexArray::AddVertexBuffer(VertexBuffer& vertexBuffer)
{
	glBindVertexArray(_uid);

	vertexBuffer.Bind();
	vertexBuffer.GetLayoutBuffer().Bind();
	_vertexBuffers.push_back(vertexBuffer);
}

void VertexArray::AddIndexBuffer(IndexBuffer& indexBuffer)
{
	glBindVertexArray(_uid);

	indexBuffer.Bind();
	_indexBuffer = indexBuffer;
}