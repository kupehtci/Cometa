#pragma once

#ifndef AURAGL_BUFFER_H
#define AURAGL_BUFFER_H

#include <cstdint>

#include "debug/Assertion.h"


/**
*	Shader Data's types common in the Graphics API libraries
*	Helps to determine the type of data
*/
enum class DataType
{
	None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
};

/**
* Shader data's type's harcoded size.
* Returns Data type's size in bytes
*/
static uint32_t DataTypeCalculateSize(DataType type)
{
	switch (type)
	{
		case DataType::Float:
			return 4;
		case DataType::Float2:
			return 8;
		case DataType::Float3:
			return 12;
		case DataType::Float4:
			return 16;
		case DataType::Mat3:
			return 36;
		case DataType::Mat4:
			return 64;
		case DataType::Int:
			return 4;
		case DataType::Int2:
			return 8;
		case DataType::Int3:
			return 12;
		case DataType::Int4:
			return 16;
		case DataType::Bool:
			return 1;
		default: 
			COMETA_WARNING("Unknown Data type for getting size");
			return 0;
	}
}

/**
 *	Get the number of elements in a type of data
 *	Can also be calculated using the size of a data type and knowing the type of individual data components
 *	Mat3 returns 3 and Mat4 returns 4 because its considered as 3 float3 vectors and 4 float4 vectors
 */
static uint32_t DataTypeCalculateNumberElements(DataType type)
{
	switch (type)
	{
	case DataType::Float:
		return 1;
	case DataType::Float2:
		return 2;
	case DataType::Float3:
		return 3;
	case DataType::Float4:
		return 4;
	case DataType::Mat3:
		return 3;
	case DataType::Mat4:
		return 4;
	case DataType::Int:
		return 1;
	case DataType::Int2:
		return 2;
	case DataType::Int3:
		return 3;
	case DataType::Int4: 
		return 4; 
	case DataType::Bool:
		return 1;
	default:
		COMETA_WARNING("Unknown Data type for counting number elements");
		return 0;
	}
}


/**
* Buffer abstract class that define the minimal structure of a Renderer API Buffer
*/
class Buffer {
protected:
	uint32_t _uid;
public:
	/**
	* Bind the buffer to the active one
	*/
	virtual void Bind() = 0;
	virtual void Unbind() = 0;


	// --------- GETTERS ---------- // 
	inline uint32_t GetUid() { return _uid; }
};

/**
	Vertex Buffer that contains vertices data
*/
class VertexBuffer : public Buffer{

public: 
	/**
	* Create a Vertex Buffer with the specified size
	* Data is not defined, so can be added as SubData for Dynamic Drawing
	*/
	VertexBuffer(uint32_t size); 

	/**
	* Create a Vertex Buffer with the specified array of vertices and size
	* Data is defined so will be set to Static drawing because data won't change
	*/
	VertexBuffer(float* vertices, uint32_t size); 

	~VertexBuffer(); 

	void Bind() override; 
	void Unbind() override; 
};

/**
* Indexes Buffer that contains Indices information for Elements Buffers
*/
class IndexBuffer : public Buffer{

private: 
	uint32_t _count; 

public:
	
	IndexBuffer(uint32_t* indices, uint32_t size);


	~IndexBuffer(); 

	void Bind() override;
	void Unbind() override;

	// ---------- GETTERS ---------- //
	inline uint32_t GetCount() { return _count;  }
};

#endif  //AURAGL_BUFFER_H