//
// Created by sebasmora on 22/3/20.
//


#ifndef GC_VSPOINTER_H
#define GC_VSPOINTER_H

#include <iostream>
#include "GarbageCollector.h"



template<class T>
class VSPtr {

    /**
     * CLASS MEMBERS
     */
private:
    T *ptr;
    std::string id;
    static GarbageCollector* garbageCollector;


public:


    /**
     * Constructor
     */
    VSPtr() {
        ptr = (T*) malloc(sizeof(T));
        id = garbageCollector->generateID();
        garbageCollector->addInstance(ptr, id);
        std::cout << "DIRECCION DE MEMORIA DEL DATO QUE GUARDA EL VSPointer " << id << "   " << ptr << "\n";
    }






    /**
    * Return the current of the current VSPtr
    * @tparam T
    * @return uint32_t id
    */
    std::string get_id(){
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
        garbageCollector->decrementRedCount(id);
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
        return newVSptr;
    }





};

/** Initialization garbage collector instance */
template <class T>
GarbageCollector* VSPtr<T>::garbageCollector = garbageCollector->getGarbageCollectorInstance();








#endif //GC_VSPOINTER_H
