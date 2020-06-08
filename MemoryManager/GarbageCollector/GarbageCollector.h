//
// Created by sebasmora on 21/3/20.
//

#ifndef GC_GARBAGECOLLECTIOR_H
#define GC_GARBAGECOLLECTIOR_H

#include <iostream>
#include <any>
#include "VSPtrInstance.h"
#include "UUID/UUID.h"
#include <thread>
#include <mutex>
#include <fstream>
#include "jsoncpp/json/json.h"
#include <map>
#include <stdio.h>



/**
 * Garbage collector class, this class manage memory od the VSPtr
 */
class GarbageCollector {



/********************************************************************************************************************
 *                                         Members and function class declaration
 ********************************************************************************************************************/

private:
    static GarbageCollector* garbageCollector;
    std::thread GCThread;
    mutable std::mutex mutex_;
    std::map<std::string, VSPrtInfo*> mapGarbageCollector;



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
     * @return An id to every VSPtr wrapper
     */
    std::string generateID() const;





    /**
     * This method add a new VSPtr instance to garbage collector's list
     * @tparam Data Type of data that holds the VSPtr
     * @param value VSPtr instance
     */
    template <typename T>
    void addInstance(const T& value, std::string& id);



    /**
     * This method increments the instance's ref count assign to the id
     * @param id instance's id
     */
    void incrementRefCount(const std::string& id);



    /**
  * This method decrements the instance's ref count assign to the id
  * @param id instance's id
  */

    void decrementRedCount(const std::string& id);




    /**
     * Print all the garbage collectot's list elements
     */
    void printGargabeCollectorInfo();




    /**
     * This methods is executed by a thread every 10 seconds to verify the ref count of every Vsptr contained in
     * the garbage collector list and delete those which its ref count is 0
     */
    void executeGarbageCollector();



    /**
     * Loops through garbage collector hash map and serialize each vsptrInfo into a json file
     */
    void generateJSON();



    /**
     * Spawn garbageCollector Thread
     * @return
     */
    std::thread spawnThread();



    /*
    template<typename T>
    void setValue(T value, std::string& id);
     */



    void setValue(std::string newValue, std::string& id);



};




/********************************************************************************************************************
 *                                         Members and function class definition
 ********************************************************************************************************************/





/********************************************************************************************************************
 *                                  Garbage collector functionality
 *******************************************************************************************************************/


/**
 * Add a new VSPointer the the garbage collector's list. First, create a VSPointerInstance that holds the VSPointer instance
 * @tparam T TYpe of data that VSPointer holds
 * @param value VSPointer
 */
template <typename T>
void GarbageCollector::addInstance(const T& value, std::string& id) {
    //printf("INSTNACIA EN ADD INSTANCE &p", value);
    VSPtrInstance<T>* vsPtrInstance = new VSPtrInstance<T>(value, id);
    mapGarbageCollector[id] = vsPtrInstance;

}


/*
template<typename T>
void GarbageCollector::setValue(T value, std::string& id) {
    VSPrtInfo* current = mapGarbageCollector[id];
    current->setValue(value);
}
 */


#endif //GC_GARBAGECOLLECTIOR_H
