#include "LayoutBuffer.h"


#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>



LayoutBuffer::~LayoutBuffer() {
	Unbind(); 
	_layouts.clear(); 
	_size = 0; 
}

void LayoutBuffer::Build() {

	_size = 0;

	if (_layouts.empty()) {
		COMETA_ASSERT("Building an empty layout buffer"); 
		return; 
	}

	uint32_t calcOffset = 0; 
	
	// For each layout position, sum the stride and size
	// 
	for (int i = 0; i < _layouts.size(); i++) {
		// _layouts[i]._position = i;		      // Positions are settled in the LayoutBuffer declaration
		_layouts[i]._offset = calcOffset;
		calcOffset += _layouts[i]._size; 
		_size += _layouts[i]._size; 
	}
}

void LayoutBuffer::Enable() {

	// Enable each layout in the LayoutBuffer depending on its type of data
	for (const Layout layout : _layouts) {
		switch (layout._type) {
		case DataType::Float: 
		case DataType::Float2: 
		case DataType::Float3: 
		case DataType::Float4: 
			glVertexAttribPointer(layout._position, 
								DataTypeCalculateNumberElements(layout._type),
								GL_FLOAT, 
								GL_FALSE, 
								_size, 
								(void*)(layout._offset));
			glEnableVertexAttribArray(layout._position); 
			break; 

		default: 
			std::cout << "not implemented yet mat3 and mat4 layout implementation" << std::endl; 
			break; 
		} 

	}
}

// TODO: Replace Enable with Bind
void LayoutBuffer::Bind() {
	Enable(); 
}

void LayoutBuffer::Unbind() {

	// Disable each layout
	for (const Layout layout : _layouts) {
		glDisableVertexAttribArray(layout._position); 
	}

	// _layouts.clear(); 

	_size = 0; 
}

void LayoutBuffer::Debug() {
	for (auto layout : _layouts) {
		std::cout << "Layout: " << layout._position << " " << layout._name << " type: " << (int)layout._type << " with stride: " << layout._size << " and offset: " << layout._offset << std::endl;
	}
}

