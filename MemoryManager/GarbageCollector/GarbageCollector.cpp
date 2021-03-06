
#include "GarbageCollector.h"


/********************************************************************************************************************
 *                                  Garbage collector functionality
 *******************************************************************************************************************/




/** Initialization of the garbage collector instance */
GarbageCollector* GarbageCollector::garbageCollector = nullptr;




/**
 * Spawn the thread
 * @return thread object
 */
std::thread GarbageCollector::spawnThread(){
    return std::thread(&GarbageCollector::executeGarbageCollector, this);
}


/**
    * Constructor garbage collector
    */
GarbageCollector::GarbageCollector() {
    GCThread = spawnThread();  //Initialize Garbage collector thread;

}

/**
 * Singleton implementation, returns the instance of the garbage collector created at the first time
 * @return garbage collector implementation
 */
GarbageCollector* GarbageCollector::getGarbageCollectorInstance() {
    if(garbageCollector == nullptr){
        printf("GARBAGE COLLECTOR INSTANCE HAS BEEN CREATED\n");
        garbageCollector = new GarbageCollector();
    }
    return garbageCollector;
}




/**
 * Generate a new ID when a VSPointer is created;
 * @return
 */
std::string GarbageCollector::generateID()const {
    return UUID::generateUUID();
}





/**
 * Prints all the garbage collector's elements
 */
void GarbageCollector::printGargabeCollectorInfo() {
    printf("\n*******************************\n");
    printf(" GARBARGE COLLECTOR LIST \n");
    printf("|             id          |   refCount |        addr       |   type  |  value  \n");
    for(std::map<std::string, VSPrtInfo*>::iterator it= mapGarbageCollector.begin(); it != mapGarbageCollector.end(); it++){
        printf("|%s |    %d       |   %p  |  %s   |   %s\n", it->second->id.c_str(), it->second->refcount,
               it->second->getAdress(), it->second->type.c_str(), it->second->getValue().c_str());
    }
    printf("\n**************************************\n");
}





/**
 * This method increments the ref instance's ref count assign to the id
 * @param id instance's id
 */
void GarbageCollector::incrementRefCount(const std::string& id) {
    std::unique_lock<std::mutex> lock(mutex_);

    if(!(mapGarbageCollector.find(id) == mapGarbageCollector.end())) {
        VSPrtInfo *current = mapGarbageCollector[id];
        current->refcount++;
        printf("INCREMENTA EL CONTADOR DE REFERENCIAS: id: %s  refCount: %d \n", current->id.c_str(),
               current->refcount);
    }

}



/**
 * This method decrements the instance's ref count assign to the id
 * @param id instance's id
 */
void GarbageCollector::decrementRedCount(const std::string& id) {
    std::unique_lock<std::mutex> lock(mutex_);

    if(!(mapGarbageCollector.find(id) == mapGarbageCollector.end())) {
        VSPrtInfo *current = mapGarbageCollector[id];
        current->refcount--;
        printf("DECREMENTA EL CONTADOR DE REFERENCIAS: id: %s  refCount: %d \n", current->id.c_str(),current->refcount);
    }

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
            std::this_thread::sleep_for(std::chrono::seconds(5));
            printGargabeCollectorInfo();
            std::unique_lock<std::mutex> locker(mutex_);
            printf("START EXECUTING THREAD 1\n");
            for(std::map<std::string, VSPrtInfo*>::iterator it= mapGarbageCollector.begin(); it != mapGarbageCollector.end(); it++){
                if(it->second->refcount == 0){
                    VSPrtInfo* vsPrtInfo = it->second;
                    printf("removing ... %s", vsPrtInfo->id.c_str());
                    mapGarbageCollector.erase(it->second->id);
                    delete vsPrtInfo;
                }
            }
            generateJSON();
            printf("FINISH EXECUTE THREAD\n");
            printf("***********************");
            locker.unlock();
        }


    } catch (const std::exception& err) {
        printf("Error %s", err.what());
        GCThread = spawnThread();

    }

}







/*********************************************************************************************************************
 *   JSON
 *********************************************************************************************************************/

/**
 * Generate a json file that stores all VSPointers instances information
 */
void GarbageCollector::generateJSON() {

    Json::StyledStreamWriter writer;
    Json::Value my_list;
    Json::Value vec(Json::arrayValue);
    for(std::map<std::string, VSPrtInfo*>::iterator it=mapGarbageCollector.begin();  it != mapGarbageCollector.end(); it++){
        VSPrtInfo* current = it->second;
        Json::Value obj;

        std::ostringstream get_addr;
        get_addr << current->getAdress();
        obj["id"] = current->id;
        obj["addr"] = get_addr.str();
        obj["type"] = current->type;
        obj["value"] = current->getValue();
        obj["refcount"] = std::to_string(current->refcount);

        vec.append(obj);

    }
    my_list["VSPtr"] = vec;
    std::ofstream file("./vsptrRemote.json");
    writer.write(file, my_list);
    file.close();
}


std::string GarbageCollector::getValue(std::string& id) {
    std::string value = mapGarbageCollector[id]->getValue();
    return value;
}


void GarbageCollector::setValue(std::string newValue, std::string& id) {
    std::cout << "HOLAA  " << newValue << "\n";
    mapGarbageCollector[id]->setValue(newValue);

}
