//
// Created by Daniel Laplana Gimeno on 30/1/25.
//

#include "Shader.h"
#include <filesystem>

Shader::Shader() {
    _shaderUID = 0;
    _shaderType = GL_NONE;
    _sourceCode = "";
    _filePath = "";
}

Shader::Shader(std::string filePath, GLenum shaderType){
    _shaderUID = 0;
    _sourceCode = "";
    _filePath = filePath;
    _shaderType = shaderType;
    LoadFromFile(filePath);
    CompileShader();
}

Shader::~Shader(){

}

std::string Shader::LoadFromFile(std::string filePath){

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

unsigned int Shader::CompileShader() {
    if(_sourceCode.empty() || _sourceCode.length() <= 0 ){
        return 0;
    }

    // Check shader type
//    if(shaderType != GL_VERTEX_SHADER && shaderType != GL_FRAGMENT_SHADER){
//        return 0;
//    }

    unsigned int uid = glCreateShader(_shaderType);
    const char* shaderSource = _sourceCode.c_str();
    glShaderSource(uid, 1, &shaderSource, NULL);
    glCompileShader(uid);

    int success;
    char infoLog[512];
    // validate shader compilation
    glGetShaderiv(uid, GL_COMPILE_STATUS, &success);

    if(!success)
    {
        glGetShaderInfoLog(uid, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        return 0;
    }
    else{
        // std::cout << "Successful fragment shader compilation" << std::endl;
    }

    _shaderUID = uid;
    return _shaderUID;
}