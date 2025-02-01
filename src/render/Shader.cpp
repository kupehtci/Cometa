//
// Created by Daniel Laplana Gimeno on 30/1/25.
//

#include "Shader.h"
#include <filesystem>

Shader::Shader() {
    _sourceCode = "";
    _filePath = "";
}

Shader::Shader(const std::string filePath){
    _sourceCode = "";
    _filePath = filePath;

    LoadShaderFromFile(filePath);
}

Shader::~Shader(){

}

std::string Shader::LoadShaderFromFile(const std::string filePath){

    // std::filesystem::path absolutePath = std::filesystem::current_path().append(filePath);

    // std::cout << "Absolute path: " << absolutePath.string() << std::endl;

    std::cout << "Reeading shader in file path: " << filePath << std::endl;
    std::ifstream file = std::ifstream(filePath);

    if(!file.is_open()){
        std::cout << "ERROR: Could not open file: " << filePath << std::endl;
        return "";
    }

    std::stringstream stream;
    stream << file.rdbuf();
    file.close();
    // set the own variables

    _filePath = filePath;
    _sourceCode = stream.str();

    // std::cout << "Read shader that contains: " << std::endl <<  _sourceCode.c_str() << std::endl;

    return _sourceCode;
}