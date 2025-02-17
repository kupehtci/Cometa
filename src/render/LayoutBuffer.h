#pragma once

#ifndef AURAGL_LAYOUTBUFFER_H
#define AURAGL_LAYOUTBUFFER_H

#include <cstdint>
#include <vector>

#include "Buffer.h"

struct Layout { 
	std::string _name; 
	uint32_t _position; 
	DataType _type;
	uint32_t _size; 
	uint32_t _offset; 

	/**
	*  Default constructor for layout
	*/
	Layout() = default;
	
	/**
	*  Complete constructor by defining minimal structure
	*  Intended to calculate offset next
	*/
	Layout(const uint32_t position, const DataType type, const std::string name) :
		_position(position), _type(type),  _name(name), 
		_offset(0)
	{
		_size = DataTypeCalculateSize(type); 
	}
};


class LayoutBuffer /* : public Buffer */{

private: 
	std::vector<Layout> _layouts; 
	uint32_t _size; 

public: 
	LayoutBuffer();

	LayoutBuffer(std::initializer_list<Layout> layouts) : _layouts(layouts) {}; 

	void Build(); 

	void Debug(); 
};

#endif // AURAGL_LAYOUTBUFFER_H