//
// Created by Daniel Laplana Gimeno on 5/12/24.
//

#include "debug/Assertion.h"

#ifndef AURAGL_SINGLETON_H
#define AURAGL_SINGLETON_H



template<class T>
class Singleton{

public:
    static T* instance;

    Singleton(){};
    ~Singleton(){};

    inline static void Create(){
        if(!instance){
            instance = new T();
        }
        else{
            Assertion::Warning("Singleton tries to be created more than once");
        }
    }

    inline static T* GetInstancePtr(){
        if(!instance){
            Create();
            return instance;
//            return nullptr;
        }
        else{
            return instance;
        }
    }
};

// Initialize the static variable
template<class T>
T* Singleton<T>::instance = nullptr;

//// This class is created to be as Parent of all the managers and stablish a group
//// of methods that can be used from all the managers
//// TODO: Implement
template<class T>
        class SingletonManager : public Singleton <T>{

public:
    virtual void Init() = 0;
    virtual void Update() = 0;
    virtual void Close() = 0;
};



#endif //AURAGL_SINGLETON_H
