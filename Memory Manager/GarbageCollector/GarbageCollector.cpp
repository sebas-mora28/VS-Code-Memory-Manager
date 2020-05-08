
#include "GarbageCollector.h"


/********************************************************************************************************************
 *                                  Garbage collector functionality
 *******************************************************************************************************************/




/** Initialization of the garbage collector instance */
GarbageCollector* GarbageCollector::garbageCollector = nullptr;




/**
 * Spawn the thread
 * @return
 */
std::thread GarbageCollector::spawnThread(){
    return std::thread(&GarbageCollector::executeGarbageCollector, this);
}




/**
    * Constructor garbage collector, declared private avoiding instance it more than once
    */
GarbageCollector::GarbageCollector() {
    GCThread = spawnThread();  //Initialize Garbage collector thread;

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
    return UUID::generateUUID();
}











/**
 * Prints all the garbage collector's elements
 */
void GarbageCollector::printGargabeCollectorInfo() {
    std::cout << "\n\n -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*" <<"\n";
    for(std::map<std::string, VSPrtInfo*>::iterator it= mapGarbageCollector.begin(); it != mapGarbageCollector.end(); it++){
        std::cout << "id  " <<  it->second->id << "   ref cout  " << it->second->refcount << "   addrr  " << it->second->getInstance() << "   type  " << it->second->getValue() << "\n";


    }
    std::cout << "\n\n -*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*" <<"\n";
}





/**
 * This method increment the ref count to the instance with the id
 * @param id instance's id
 */
void GarbageCollector::incrementRefCount(const std::string& id) {
    std::unique_lock<std::mutex> lock(mutex_);
    VSPrtInfo* current = mapGarbageCollector[id];
    current->refcount++;
    std::cout << "INCREMENTA EL CONTADOR DE REFERENCIAS     " << current->id << "     " <<  current->refcount << "\n\n";

}



/**
 * This method decrement the ref count to the instance with the id
 * @param id instance's id
 */
void GarbageCollector::decrementRedCount(const std::string& id) {
    std::unique_lock<std::mutex> lock(mutex_);
    VSPrtInfo* current = mapGarbageCollector[id];
    current->refcount--;
    std::cout << " DECREMENTA EL CONTADOR DE REFERENCIA" << current->id << "     " <<  current->refcount << "\n";

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
        while(true){
            std::this_thread::sleep_for(std::chrono::seconds(10));
            std::unique_lock<std::mutex> locker(mutex_);
            std::cout << "THREAD START EXECUTING" << "\n";
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
            locker.unlock();
        }


    } catch (const std::exception& err) {
        std::cout << "ERROR" <<  err.what() << "\n";
        GCThread = spawnThread();

    }

}







/*********************************************************************************************************************
 *   JSON
 *********************************************************************************************************************/

void GarbageCollector::generateJSON() {

    Json::StyledStreamWriter writer;
    Json::Value my_list;
    Json::Value vec(Json::arrayValue);
    for(std::map<std::string, VSPrtInfo*>::iterator it=mapGarbageCollector.begin();  it != mapGarbageCollector.end(); it++){
        VSPrtInfo* current = it->second;
        Json::Value obj;

        std::ostringstream get_addr;
        get_addr << current->getInstance();

        obj["id"] = current->id;
        obj["addr"] = get_addr.str();
        obj["type"] = current->type;
        obj["value"] = current->getValue();
        obj["refcount"] = std::to_string(current->refcount);

        vec.append(obj);

    }
    my_list["VSPtr"] = vec;
    std::ofstream file("./lib/vsptr.json");
    std::cout << file.is_open() << "\n";
    writer.write(file, my_list);
    file.close();
}
