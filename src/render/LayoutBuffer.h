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
	std::vector<Layout> _layouts;	// Array of layouts that compose the structure of the LayoutBuffer
	uint32_t _size;					// Total stride of the LayoutBuffer

public: 
	/**
	*	Default constructor for LayoutBuffer
	*/
	LayoutBuffer();

	/**
	* Struct similar constructor for the LayooutBuffer
	* Allows to create a LayoutBuffer like this: 
	*		LayoutBuffer layBuffer = {{0, DataType::Float3, "_position"}, {1, DataType::Float3, "_color"}}
	* 
	* In a format like a struct declaration
	*/
	LayoutBuffer(std::initializer_list<Layout> layouts) : _layouts(layouts) {}; 

	/**
	*   Build the layout buffer by calculating the stride and offset of each layout
	*/
	void Build(); 


	/**
	*	Enable the LayoutBuffer by enabling each layout
	*/
	void Enable(); 

	/**
	* Debug function that print by console the properties of each layout within the LayoutBuffer
	*/
	void Debug(); 
};

#endif // AURAGL_LAYOUTBUFFER_H