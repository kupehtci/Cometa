#pragma once

#include "Buffer.h"

class VertexArray : public Buffer {

private: 

public: 
	VertexArray();
	~VertexArray();

	void Bind() override;
	void Unbind() override;
};