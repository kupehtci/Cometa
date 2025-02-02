//
// Created by Daniel Laplana Gimeno on 5/12/24.
//
#include <stdio.h>
#include <iostream>

#ifndef AURAGL_ASSERTION_H
#define AURAGL_ASSERTION_H

#define COMETA_DEBUG

#ifdef COMETA_DEBUG
    #define COMETA_ASSERT(x) Assertion::Assert(x)
    #define COMETA_ERROR(x) Assertion::Error(x)
    #define COMETA_WARNING(x) Assertion::Warning(x)
#else
    #define COMETA_ASSERT(x) ((void)0)
    #define COMETA_ERROR(x) ((void)0)
    #define COMETA_WARNING(x) ((void)0)
#endif

enum AssertLevel{
    Debug = 0, Warning, Error
};

class Assertion{

public:
    inline static void Assert(const char* msg){
        std::cout << "[INFO]: " << msg << std::endl;
    }

    inline static void Error(const char* msg){
        std::cout << "[ERROR]: " << msg << std::endl;
    }

    inline static void Warning(const char* msg){
        std::cout << "[WARNING]: " << msg << std::endl;
    }
};

#endif //AURAGL_ASSERTION_H
