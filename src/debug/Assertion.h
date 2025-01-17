//
// Created by Daniel Laplana Gimeno on 5/12/24.
//
#include <stdio.h>
#include <iostream>

#ifndef AURAGL_ASSERTION_H
#define AURAGL_ASSERTION_H



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
