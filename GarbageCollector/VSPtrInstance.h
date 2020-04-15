//
// Created by sebasmora on 22/3/20.
//

#ifndef VS_CODE_MEMORY_MANAGER_VSPTRINSTANCE_H
#define VS_CODE_MEMORY_MANAGER_VSPTRINSTANCE_H

#include <iostream>


template <class T>
class VSPtr;



/**
 * VSPtr class, this class holds the reference count of each VSPtr instance
 */
struct VSPrtInfo{

public:
    int refcount;
    uint32_t  id;


    virtual void* getInstance();


};

void *VSPrtInfo::getInstance() {
    return nullptr;
}


/**
 * Struct that holds a VSPtr
 * @tparam T
 */
template <typename T>
struct VSPtrInstance: public VSPrtInfo{

public:


private:
    /**VSPtr instance*/
    T instance;



    /**
     * VSPtr constructor
     * @param instance VSPtr instance
     */

public:
    explicit VSPtrInstance(T instance, uint32_t& id);



    /**
    * This method return that VSPtr instance that holds VSPtrInstance
    * @tparam T
    * @return
    */
    //T getInstance();




    void* getInstance() override {
        return instance;
    }


    /***
     * This mehods the id
     * @return
     */
    uint32_t getId();



    /**
    * This method add a new instance to the garbage collector list
    * @tparam T
    * @param instance
    */
    ~VSPtrInstance(){
        delete this;
    }


};






/********************************************************************************************************************
 *                                         Members and function class definition
 ********************************************************************************************************************/



/**
 * This method add a new instance to the garbage collector list
 * @tparam T
 * @param instance
 */
template<typename T>
VSPtrInstance<T>::VSPtrInstance(T instance, uint32_t& id){
    VSPrtInfo::refcount = 1;
    VSPrtInfo::id = id;
    this->instance = instance;
    std::cout << "INSTANCIA GUARDADA EN VSptrInstance " << instance << "   " << this->instance <<  "\n";
}



/**
 * This method return that VSPtr's instance that holds VSPtrInstance
 * @tparam T
 * @return

template<typename T>
T VSPtrInstance<T>::getInstance() {
    return instance;
}
 */


template<typename T>
uint32_t VSPtrInstance<T>::getId() {
    return this->id;
}

#endif //VS_CODE_MEMORY_MANAGER_VSPTRINSTANCE_H
