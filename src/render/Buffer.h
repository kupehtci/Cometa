#pragma once

#ifndef AURAGL_BUFFER_H
#define AURAGL_BUFFER_H

#include <cstdint>

#include "debug/Assertion.h"
#include "./DataType.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>



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