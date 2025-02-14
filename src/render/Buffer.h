#pragma once
#include <cstdint>


#include "debug/Assertion.h"


/**
*	Shader Data's types common in the Graphics API libraries
*	Helps to determine the type of data
*/
enum class ShaderDataType
{
	None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
};

/**
* Shader data's type's harcoded size.
* Returns Data type's size in bytes
*/
static uint32_t ShaderDataTypeSize(ShaderDataType type)
{
	switch (type)
	{
		case ShaderDataType::Float:    
			return 4;
		case ShaderDataType::Float2:   
			return 8;
		case ShaderDataType::Float3:   
			return 12;
		case ShaderDataType::Float4:   
			return 16;
		case ShaderDataType::Mat3:     
			return 36;
		case ShaderDataType::Mat4:     
			return 64;
		case ShaderDataType::Int:      
			return 4;
		case ShaderDataType::Int2:     
			return 8;
		case ShaderDataType::Int3:     
			return 12;
		// case ShaderDataType::Int4:     return 16;
		case ShaderDataType::Bool:     
			return 1;
	}

	COMETA_WARNING( "Unknown ShaderDataType!");
	return 0;
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
