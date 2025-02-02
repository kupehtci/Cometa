//
// Created by Daniel Laplana Gimeno on 30/1/25.
//

#ifndef AURAGL_SHADER_H
#define AURAGL_SHADER_H

#include <iostream>
#include <fstream>
#include <sstream>

#include "glad/glad.h"
#include <GLFW/glfw3.h>


/**
 * Class that represents a GSLS Shader and offers the utility to use them
 */
class Shader {

private:

    unsigned int _shaderUID;
    std::unordered_map<GLenum, std::string> _shaderSources;
    std::unordered_map<GLenum, std::string> _filePaths;
    std::string _debugName;


public:

    /**
     * CONSTRUCTOR
     * Create a shader program composed of a Vertex and Fragment shader references by its source.
     * @param name (std::string) Debug name assigned to the shader
     * @param vertexShaderSource (const std::string&) Vertex Shader source's path
     * @param fragmentShaderSource (const std::string&) Fragment Shader source's path
     */
    Shader(const std::string& name, const std::string& vertexShaderSource, const std::string& fragmentShaderSource );

    /**
     * Default destructor of the shader
     */
    ~Shader();

private:
    /**
     * Load a shader from a file using an stream and retunrns the shader as an string
     * @param filePath Path to the file that is being loaded as a shader
     * @return (string) shader loaded as string
     */
    std::string LoadFromFile(std::string filePath);

    /**
     * Create a shader buffer in OpenGL, link the source and compile it
     * Once it has been generated it returns the UID of the buffered shader
     * If shader has not been loaded in Shader's source or some error ocurred during shader compilation it will return 0
     * @return (unsigned int) UID of the shader compilated
     */
    unsigned int CompileShader(GLenum shaderType);

    /**
     * Compile the shader program by compiling each one of the shaders and then link them into the program
     * Once are all linked the shaders are detached and deleted its compilation
     */
    void CompileShaderProgram();


public:
    /**
     * Delete the shader program in OpenGL by its reference
     */
     void Delete();

    // ----------------- GETTERS AND SETTERS -----------------

public:
    /**
     * Get the source code of one of the loaded shaders
     */
    inline std::string GetSourceCode(GLenum shaderType){
        return _shaderSources[GL_FRAGMENT_SHADER];
    }

    /**
     * Get the file path of the shader that is loaded
     * @return
     */
    inline std::string GetFilePath(GLenum shaderType){
        return _filePaths[shaderType];
    }

    /**
     * Get the Shader's Unique ID
     * If shader has not be compiled yet correctly the UID will be 0
     * @returns (unsigned int) Shader's Unique ID that can be used as a reference to it
     */
     inline unsigned int GetShaderUID() const{
         return _shaderUID;
     }

};


#endif //AURAGL_SHADER_H
