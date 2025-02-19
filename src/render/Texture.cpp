#include "Texture.h"


Texture::Texture() {
	_uid = 0;
	_uid = 0;
	_path = "";
	_width = _height = 0;
	_channels = 0;

}

Texture::Texture(std::string filePath){

	_uid = 0;
	_path = filePath; 
	_width = _height = 0; 
	_channels = 0; 
	
	// Load image using STBI
	int width, height, nrChannels;
	const char* texture0Path = filePath.c_str();
	stbi_uc* data = nullptr; 

	data = stbi_load(texture0Path, &width, &height, &nrChannels, 0);

	// Check that channels in RGB are 3 or 4
	if (nrChannels != 3 && nrChannels != 4) {
		COMETA_ERROR("Texture format not supported"); 
	}

	if (data != nullptr) {
		glGenTextures(1, &_uid);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glBindTexture(GL_TEXTURE_2D, _uid);

		GLenum format = nrChannels == 4 ? GL_RGBA : GL_RGB; 
		GLenum internalFormat = nrChannels == 4 ? GL_RGBA8 : GL_RGB8; 

		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, _width, _height, 0, format, GL_UNSIGNED_BYTE, data);
		// glTextureSubImage2D

		stbi_image_free(data);
	}
	else {
		COMETA_ERROR("Unable to load texture"); 
		return; 
	}

}


void Texture::Bind(GLenum textureNumber) {
	glActiveTexture(textureNumber);
	//glBindTexture(GL_TEXTURE_2D, _uid);
}

bool const Texture::operator==(const Texture& other) {
	return (_uid == other._uid); 
}