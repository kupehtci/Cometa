#include "Texture.h"

Texture::Texture() {

}

Texture::Texture(std::string filePath){

}


void Texture::Bind() {

}

bool const Texture::operator==(const Texture& other) {
	return (_uid == other._uid); 
}