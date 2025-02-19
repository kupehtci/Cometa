#ifndef COMETA_TEXTURE_H
#define COMETA_TEXTURE_H

#include <cstdint>
#include <string>

// #include "Window.h"
#include <glm.hpp>

class Texture {

private: 
	uint32_t _uid;			// Unique ID of the loaded texture. In OpenGL this uid references the texture
	uint32_t _width;		// Width of the loaded texture
	uint32_t _height;		// Height of the loaded texture
	std::string _path;		// Store the path of the loaded texture

public: 
	Texture() = default; 

	Texture(std::string filePath); 

	void Bind(); 

	// Operator overload
	
	bool const operator==(const Texture& other);



public:

	inline uint32_t GetWidth() { return _width; }
	inline uint32_t GetHeight() { return _height;  }
	inline glm::vec2 GetSize() { return glm::vec2(_width, _height); }
	inline std::string GetPath() { return _path; }
};

#endif