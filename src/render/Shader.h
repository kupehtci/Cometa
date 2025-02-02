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
    GLenum _shaderType;
    // Source code of the shader
    std::string _sourceCode;
    std::string _filePath;
    std::string _name;

    // New variables

public:

    /**
     * Shader default constructor
     */
    Shader();

    /**
     * Shader constructor that loads the shader from the file path speficied
     * @param filePath (const string) file path of the shader to load
     */
    Shader(std::string filePath, GLenum shaderType);

    /**
     * Default destructor of the shader
     */
    ~Shader();

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
     * @param shaderType (GLenum) indicate the type of shader to compile
     * @return (unsigned int) UID of the shader compilated
     */
    unsigned int CompileShader();

    /**
     * Delete the shader in OpenGL by its reference
     */
    void DeleteShader();

    // ----------------- GETTERS AND SETTERS -----------------

public:
    /**
     * Get the source code of the loaded shader
     */
    inline std::string GetSourceCode() const{
        return _sourceCode;
    }

    /**
     * Get the file path of the shader that is loaded
     * @return
     */
    inline std::string GetFilePath() const{
        return _filePath;
    }

    /**
     * Get the Shader's Unique ID
     * If shader has not be compiled yet correctly the UID will be 0
     * @returns (unsigned int) Shader's Unique ID that can be used as a reference to it
     */
     inline unsigned int GetShaderUID() const{
         return _shaderUID;
     }

     /**
      * Get the shader type
      * @return (GLenum) Shader's type
      */
     inline GLenum GetShaderType() const{
         return _shaderType;
     }

     /**
      * Check if shader has been already compiled
      * @return
      */
     inline bool IsCompiled() const{
         return _shaderType != 0;
     }

};


#endif //AURAGL_SHADER_H
