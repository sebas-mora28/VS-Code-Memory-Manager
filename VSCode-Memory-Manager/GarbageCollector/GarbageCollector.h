
#ifndef GC_GARBAGECOLLECTIOR_H
#define GC_GARBAGECOLLECTIOR_H

#include "VSPtrInstance.h"
#include "UUID.h"
#include <thread>
#include <mutex>
#include <sstream>
#include <fstream>
#include "jsoncpp/json/json.h"
#include <map>
#include <condition_variable>


template <typename T>
class VSPtr;



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
     * This method increment the ref count to the instance with the id
     * @param id instance's id
     */
    void incrementRefCount(const std::string& id);



    /**
  * This method decrement the ref count to the instance with the id
  * @param id instance's id
  */

    void decrementRedCount(const std::string& id);




    /**
     * Print all the garbage collectot's list elements
     */
    void printGargabeCollectorInfo();




    /**
     * This methods is executed by a thread every 10 seconds to verify which the ref count of every Vsptr contained in
     * the garbage collector list and delete those which its ref count is 0
     */

    void executeGarbageCollector();



    void generateJSON();



    std::thread spawnThread();



};




/********************************************************************************************************************
 *                                         Members and function class definition
 ********************************************************************************************************************/




/********************************************************************************************************************
 *                                  Garbage collector functionality
 *******************************************************************************************************************/



/** Initialization of the garbage collector instance */
GarbageCollector* GarbageCollector::garbageCollector = nullptr;




std::thread GarbageCollector::spawnThread(){
    return std::thread(&GarbageCollector::executeGarbageCollector, this);
}


/**
    * Constructor garbage collector, declared private avoiding instance it more than once
    */
GarbageCollector::GarbageCollector() {
    GCThread = spawnThread(); //Initialize Garbage collector thread ;

}

/**
 * Singleton implementation, returns the instance of the garbage collector created at the first time
 * @return garbage collector implementation
 */
GarbageCollector*GarbageCollector::getGarbageCollectorInstance() {
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
std::string GarbageCollector::generateID() const {
    return generateUUID();
}







/**
 * Add a new VSPointer the the garbage collector's list. First, create a VSPointerInstance that holds the VSPointer instance
 * @tparam T TYpe of data that VSPointer holds
 * @param value VSPointer
 */
template <typename T>
void GarbageCollector::addInstance(const T& value, std::string& id) {
    std::cout << "INSTANCIA EN ADD INSTANCE " <<  value << "\n";
    VSPtrInstance<T>* vsPtrInstance = new VSPtrInstance<T>(value, id);
    mapGarbageCollector[id] = vsPtrInstance;
    //listGc.add(vsPtrInstance);
}





/**
 * Prints all the garbage collector's elements
 */

void GarbageCollector::printGargabeCollectorInfo() {
    std::cout << "\n\n -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*" <<"\n";
    for(std::map<std::string, VSPrtInfo*>::iterator it= mapGarbageCollector.begin(); it != mapGarbageCollector.end(); it++){
        std::cout << "id  " <<  it->second->id << "   ref cout  " << it->second->refcount << "   addrr  " << it->second->getInstance() << "   type  " << it->second->type << "\n";


    }
    std::cout << "\n\n -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*" <<"\n";
}





/**
 * This method increment the ref count to the instance with the id
 * @param id instance's id
 */
void GarbageCollector::incrementRefCount(const std::string& id) {
    std::cout << "INCREMENTA EL CONTADOR DE REFERENCIAS " << "\n";
    //VSPrtInfo* current = garbageCollector->listGc.getByID(id);
    VSPrtInfo* current = mapGarbageCollector[id];
    current->refcount++;
    executeGarbageCollector();
    std::cout << "PRINT DESDE EL GARBAGE COLLECTOR PARA DECREMENTA SU REFERENCIA     " << current->id << "     " <<  current->refcount << "\n";

}




/**
 * This method decrement the ref count to the instance with the id
 * @param id instance's id
 */
void GarbageCollector::decrementRedCount(const std::string& id) {
    std::cout << "DECREMENTA EL CONTADOR DE REFERENCIAS " << "\n";
    //VSPrtInfo* current = garbageCollector->listGc.getByID(id);
    VSPrtInfo* current = mapGarbageCollector[id];
    current->refcount--;
    std::cout << "PRINT DESDE EL GARBAGE COLLECTOR PARA DECREMENTAR SU REFERENCIA" << current->id << "     " <<  current->refcount << "\n";
    executeGarbageCollector();

}





/*********************************************************************************************************************
 *   Thread
 *********************************************************************************************************************/





/**
 * This method is executed every 5 seconds by the GB collector thread. Verify is one of the instance contained in the map
 * has 0 reference to delete it. Besides call the function to generate the JSON file
 */

void GarbageCollector::executeGarbageCollector() {


    try{
        std::unique_lock<std::mutex> locker(mutex_);

        std::cout << "THREAD START EXECUTING" << "\n";
        std::this_thread::sleep_for(std::chrono::seconds(10));

        for(std::map<std::string, VSPrtInfo*>::iterator it= mapGarbageCollector.begin(); it != mapGarbageCollector.end(); it++){

            if(it->second->refcount == 0){
                VSPrtInfo* vsPrtInfo = it->second;
                std::cout << "removing ..." << vsPrtInfo->id << "\n";
                mapGarbageCollector.erase(it->second->id);
                delete vsPrtInfo;
            }
        }
        generateJSON();
        std::cout << "SALE DE EXECUTE GC" << "\n";
        std::cout << "\n\n***************************** \n\n";


    } catch (const std::exception& err) {
        std::cout << err.what() << "\n";
        GCThread = spawnThread();

    }

}







/*********************************************************************************************************************
 *   JSON
 *********************************************************************************************************************/

void GarbageCollector::generateJSON() {

    std::cout << "\n\n\n ************************** \n\n\n";
    Json::StyledStreamWriter writer;
    Json::Value my_list;

    Json::Value vec(Json::arrayValue);
    for(std::map<std::string, VSPrtInfo*>::iterator it=mapGarbageCollector.begin();  it != mapGarbageCollector.end(); it++){
        VSPrtInfo* current = it->second;

        Json::Value obj;

        std::ostringstream get_addr;
        get_addr << current->getInstance();
        std::cout << get_addr.str() << "\n";

        obj["id"] = current->id;
        obj["addr"] = get_addr.str();
        obj["type"] = current->type;
        obj["ref count"] = current->refcount;


        vec.append(obj);

    }
    my_list["VSPtr"] = vec;
    std::ofstream file("../test.json");
    writer.write(file, my_list);
    file.close();

    std::cout << "\n\n\n ************************** \n\n\n";

}



#endif //GC_GARBAGECOLLECTIOR_H
