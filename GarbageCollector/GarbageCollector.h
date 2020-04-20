//
// Created by sebasmora on 21/3/20.
//

#ifndef GC_GARBAGECOLLECTIOR_H
#define GC_GARBAGECOLLECTIOR_H

#include "VSPtrInstance.h"
#include "../List/ListGC.h"
#include "UUID.h"



template <typename T>
class VSPtr;



/**
 * Garbage collector class, this class manage memory od the VSPtr
 */
class GarbageCollector {

private:
    static GarbageCollector* garbageCollector;
    ListGC<VSPrtInfo*> listGc;


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
    std::string generateID();



    /**
     * This method add a new VSPtr instance to garbage collector's list
     * @tparam Data Type of data that holds the VSPtr
     * @param value VSPtr instance
     */
    template <typename T>
    void addInstance(T& value, std::string& id);





    /**
     * This method increment the ref count to the instance with the id
     * @param id instance's id
     */
    void incrementRefCount(std::string& id);



    /**
  * This method decrement the ref count to the instance with the id
  * @param id instance's id
  */

    void decrementRedCount(std::string& id);


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


/**
    * Constructor garbage collector, declared private avoiding instance it more than once
    */
GarbageCollector::GarbageCollector(){
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
std::string GarbageCollector::generateID() {
    return generateUUID();
}





/**
 * Add a new VSPointer the the garbage collector's list. First, create a VSPointerInstance that holds the VSPointer instance
 * @tparam T TYpe of data that VSPointer holds
 * @param value VSPointer
 */
template <typename T>
void GarbageCollector::addInstance(T& value, std::string& id) {
    std::cout << "INSTANCIA EN ADD INSTANCE " <<  value << "\n";
    VSPtrInstance<T>* vsPtrInstance = new VSPtrInstance<T>(value, id);
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
void GarbageCollector::incrementRefCount(std::string& id) {
    std::cout << "INCREMENTA EL CONTADOR DE REFERENCIAS " << "\n";
    VSPrtInfo* current = garbageCollector->listGc.getByID(id);
    current->refcount++;
    std::cout << "PRINT DESDE EL GARBAGE COLLECTOR PARA DECREMENTA SU REFERENCIA" << current->id << "     " <<  current->refcount << "\n";

}









/**
 * This method decrement the ref count to the instance with the id
 * @param id instance's id
 */
void GarbageCollector::decrementRedCount(std::string& id) {
    std::cout << "DECREMENTA EL CONTADOR DE REFERENCIAS " << "\n";
    VSPrtInfo* current = garbageCollector->listGc.getByID(id);
    current->refcount--;
    std::cout << "PRINT DESDE EL GARBAGE COLLECTOR PARA INCREMENTAR SU REFERENCIA" << current->id << "     " <<  current->refcount << "\n";

}




#endif //GC_GARBAGECOLLECTIOR_H
