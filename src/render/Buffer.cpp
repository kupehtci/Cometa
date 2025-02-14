#include "Buffer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// --------- Vertex Buffer ---------

VertexBuffer::VertexBuffer(uint32_t size) {
	glGenBuffers(1, &_uid); 
	glBindBuffer(GL_ARRAY_BUFFER, _uid); 
	glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW); 

	COMETA_ASSERT("Created vertex buffer");
}

VertexBuffer::VertexBuffer(float* vertices, uint32_t size) {
	glGenBuffers(1, &_uid);
	glBindBuffer(GL_ARRAY_BUFFER, _uid);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

	COMETA_ASSERT("Created vertex buffer"); 

}

VertexBuffer::~VertexBuffer() {
	glDeleteBuffers(1, &_uid); 
}

void VertexBuffer::Bind() {
	glBindBuffer(GL_ARRAY_BUFFER, _uid); 
}

void VertexBuffer::Unbind() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}


// ---------- Index Buffer ---------

IndexBuffer::IndexBuffer(uint32_t* indices, uint32_t size) {
	_count = size; 
	glGenBuffers(1, &_uid);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _uid);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);

	COMETA_ASSERT("Created index buffer");
}

IndexBuffer::~IndexBuffer() {
	glDeleteBuffers(1, &_uid); 
}

void IndexBuffer::Bind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _uid); 
}

void IndexBuffer::Unbind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}