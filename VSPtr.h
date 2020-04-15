//
// Created by david on 22/3/20.
//

#ifndef VS_CODE_MEMORY_MANAGER_VSPTR_H
#define VS_CODE_MEMORY_MANAGER_VSPTR_H

#include <iostream>
#include "GarbageCollector/GarbageCollector.h"

using namespace std;


template<class T>
class VSPtr {

    /**
     * CLASS MEMBERS
     */
private:
    T *ptr;
    uint32_t id;

    static GarbageCollector* garbageCollector;



public:


    /**
     * Constructor
     */
    VSPtr() {
        ptr = (T*) malloc(sizeof(T));
        id = garbageCollector->generateID();
        garbageCollector->addInstance(ptr);
        std::cout << "DIRECCION DE MEMORIA DEL DATO QUE GUARDA EL VSPointer " << id << "   " << ptr << "\n";
    }





    /**
    * Return the current of the current VSPtr
    * @tparam T
    * @return uint32_t id
    */
    uint32_t get_id(){
        return this->id;
    }


    /**
    * Return the ptr that VSPtr holds
    * @tparam T
    * @return
    */
    T* get_ptr() {
        return this->ptr;
    }




    /**
     * Sets the VSPtr id
     * @param newid
     */
    void set_id(uint32_t newid){
        this->id = newid;
    }



    static GarbageCollector* getGc(){
        return garbageCollector;
    }




    /**
     * Copy constructor
     * @param p
     */
    VSPtr(const VSPtr &p) {
        ptr = p.ptr;
        std::cout << "Copia" << "\n";
    }




    /**
     * Destructor
     */

    ~VSPtr() {
        std::cout << "DESTRUCTOR" << "\n";
        delete (ptr);
    }



    /**
     * Overload = operator
     * @param other
     * @return
     */

    VSPtr<T>& operator=(VSPtr& other) {
        std::cout << "ENTRA OPERATOR = Y EL ID ES " <<  id <<   "\n";
        std::cout << "Pointer to Pointer " << "\n";
        garbageCollector->decrementRedCount(id);
        ptr = other.get_ptr();
        id = other.get_id();
        garbageCollector->incrementRefCount(id);
        garbageCollector->printGargabeCollectorInfo();
        return *this;
    }




    /**
     * Overlodad the = operator
     * @param element
     * @return
     */
    VSPtr& operator=(T element) {
        std::cout << "Pointer to Data" << "\n";
        ptr = new T(element);
        return *this;
    }






    /**
     * Overlodad & operato
     * @return
     */
    T& operator&() {
        std::cout << "OPERADOR & ";
        return *ptr;
    }




    /**
     * Overload the * operator
     * @return
     */
    T& operator*() {
        std::cout << "OPERADOR *"  << ptr << "\n";
        return *ptr;
    }




    /**
     * Overload -> operator
     */
    VSPtr<T>& operator->(){
        return &this;
    }




    /**
     *
     * @return
     */
    static VSPtr<T> New() {
        VSPtr<T> newVSptr {VSPtr<T>()};
        garbageCollector->printGargabeCollectorInfo();
        return newVSptr;
    }



};


/** Initialization garbage collector instance */
template <class T>
GarbageCollector* VSPtr<T>::garbageCollector = garbageCollector->getGarbageCollectorInstance();


#endif //VS_CODE_MEMORY_MANAGER_VSPTR_H
