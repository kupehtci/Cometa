//
// Created by Daniel Laplana Gimeno on 30/1/25.
//

#ifndef AURAGL_SHADER_H
#define AURAGL_SHADER_H

#include <iostream>
#include <fstream>
#include <sstream>

/**
 * Class that represents a GSLS Shader and offers the utility to use them
 */
class Shader {

private:

    // Source code of the shader
    std::string _sourceCode;
    std::string _filePath;
    std::string _name;

public:

    /**
     * Shader default constructor
     */
    Shader();

    /**
     * Shader constructor that loads the shader from the file path speficied
     * @param filePath (const string) file path of the shader to load
     */
    Shader(const std::string filePath);

    /**
     * Default destructor of the shader
     */
    ~Shader();

    /**
     * Load a shader from a file using an stream and retunrns the shader as an string
     * @param filePath Path to the file that is being loaded as a shader
     * @return (string) shader loaded as string
     */
    std::string LoadShaderFromFile(const std::string filePath);



    // ----------------- GETTERS AND SETTERS -----------------

public:
    /**
     * Get the source code of the loaded shader
     */
    inline std::string GetSourceCode(){
        return _sourceCode;
    }

    /**
     * Get the file path of the shader that is loaded
     * @return
     */
    inline std::string GetFilePath(){
        return _filePath;
    }

};


#endif //AURAGL_SHADER_H
