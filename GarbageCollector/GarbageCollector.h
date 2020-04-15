//
// Created by sebasmora on 21/3/20.
//

#ifndef VS_CODE_MEMORY_MANAGER_GARBAGECOLLECTIOR_H
#define VS_CODE_MEMORY_MANAGER_GARBAGECOLLECTIOR_H

#include "VSPtrInstance.h"
#include "../List/ListGC.h"
#include <thread>


template <typename T>
class VSPtr;



/**
 * Garbage collector class, this class manage memory od the VSPtr
 */
class GarbageCollector {

private:
    static GarbageCollector* garbageCollector;
    static uint32_t nextID;
    ListGC<VSPrtInfo*> listGc;


private:

    /**
     * Constructor declaration
     * It's been declared private avoiding instance it more than once
     */
    GarbageCollector();



public:



    /**
     * Singleton methods that return the garbage collector method
     * @return Pointer to the GarbageCollector instace
     */
    static GarbageCollector* getGarbageCollectorInstance();



    /**
     * This method return a ID for each VSPtr instance
     * @return
     */
    uint32_t generateID();



    /**
     * This method add a new VSPtr instance to garbage collector's list
     * @tparam Data Type of data that holds the VSPtr
     * @param value VSPtr instance
     */
    template <typename T>
    void addInstance(T& value);





    /**
     * This method increment the ref count to the instance with the id
     * @param id instance's id
     */
    void incrementRefCount(uint32_t id);



    /**
  * This method decrement the ref count to the instance with the id
  * @param id instance's id
  */

    void decrementRedCount(uint32_t id);


    /**
     * Print all the garbage collectot's list elements
     */
    void printGargabeCollectorInfo();

};




/********************************************************************************************************************
 *                                         Members and function class definition
 ********************************************************************************************************************/



/** Initialization of the garbage collector instance */
GarbageCollector* GarbageCollector::garbageCollector = nullptr;


/** Initialization of Id member class*/
uint32_t GarbageCollector::nextID = 0;



/**
    * Constructor garbage collector, declared private avoiding instance it more than once
    */
GarbageCollector::GarbageCollector(){
    nextID = 0;
    ListGC<VSPrtInfo*>();
}


/**
 * Singleton implementation, returns the instance of the garbage collector created at the first time
 * @return garbage collector implementation
 */
GarbageCollector*GarbageCollector::getGarbageCollectorInstance
() {
    if(garbageCollector == nullptr){
        std::cout << "GABARGE COLLECTOR INSTANCE HAS BEEN CREATED" << "\n";
        garbageCollector = new GarbageCollector();
    }
    return garbageCollector;
}





/**
 * Generate a new ID when a VSPointer is created;
 * @return
 */
uint32_t GarbageCollector::generateID() {
    return ++nextID;
}





/**
 * Add a new VSPointer the the garbage collector's list. First, create a VSPointerInstance that holds the VSPointer instance
 * @tparam T TYpe of data that VSPointer holds
 * @param value VSPointer
 */
template <typename T>
void GarbageCollector::addInstance(T& value) {
    std::cout << "INSTANCIA EN ADD INSTANCE " <<  value << "\n";
    VSPtrInstance<T>* vsPtrInstance = new VSPtrInstance<T>(value, nextID);
    listGc.add(vsPtrInstance);
}







/**
 * Prints all the garbage collector's elements
 */

void GarbageCollector::printGargabeCollectorInfo() {
    listGc.print();
}




/**
 * This method increment the ref count to the instance with the id
 * @param id instance's id
 */
void GarbageCollector::incrementRefCount(uint32_t id) {
    std::cout << "INCREMENTA EL CONTADOR DE REFERENCIAS " << "\n";
    VSPrtInfo* current = garbageCollector->listGc.getByID(id);
    current->refcount++;
    std::cout << "PRINT DESDE EL GARBAGE COLLECTOR PARA DECREMENTA SU REFERENCIA" << current->id << "     " <<  current->refcount << "\n";

}









/**
 * This method decrement the ref count to the instance with the id
 * @param id instance's id
 */
void GarbageCollector::decrementRedCount(uint32_t id) {
    std::cout << "DECREMENTA EL CONTADOR DE REFERENCIAS " << "\n";
    VSPrtInfo* current = garbageCollector->listGc.getByID(id);
    current->refcount--;
    std::cout << "PRINT DESDE EL GARBAGE COLLECTOR PARA INCREMENTAR SU REFERENCIA" << current->id << "     " <<  current->refcount << "\n";

}


#endif //VS_CODE_MEMORY_MANAGER_GARBAGECOLLECTIOR_H
