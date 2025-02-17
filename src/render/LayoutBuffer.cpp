#include "LayoutBuffer.h"

void LayoutBuffer::Build() {

	_size = 0;

	if (_layouts.empty()) {
		COMETA_ASSERT("Building an empty layout buffer"); 
		return; 
	}

	uint32_t calcOffset = 0; 
	
	// For each layout position, sum the stride and size
	for (int i = 0; i < _layouts.size(); i++) {
		_layouts[i]._position = i;
		_layouts[i]._offset = calcOffset;
		calcOffset += _layouts[i]._size; 
		_size += _layouts[i]._size; 
	}
}

void LayoutBuffer::Debug() {
	for (auto layout : _layouts) {
		std::cout << "Layout: " << layout._position << " " << layout._name << " type: " << (int)layout._type << " with stride: " << layout._size << " and offset: " << layout._offset << std::endl;
	}
}

