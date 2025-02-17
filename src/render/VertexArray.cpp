
#include "VertexArray.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

VertexArray::VertexArray() {
	glGenVertexArrays(1, &_uid); 
}

VertexArray::~VertexArray() {
	glDeleteVertexArrays(1, &_uid); 
}

void VertexArray::Bind() {
	glBindVertexArray(_uid);
}

void VertexArray::Unbind() {
	glBindVertexArray(0); 
}