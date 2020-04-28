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
    * This method parses the garbage collector list and generates a JSON file with the Content of the list.
    */

    void generateJSON();

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

/**
 * This method returns the type of the VSPtr.
 * @param entry
 * @return std::string
 */

template <class T>
std::string getType(T entry){
    std::string result = typeid(entry).name();

    if (result == "Pv"){
        return "void";
    }else if(result == "Pi"){
        return "int";
    }else if(result == "Pb"){
        return "bool";
    }else if(result == "NSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE"){
        return "string";
    }else if(result == "Pc"){
        return "char";
    }else if(result == "Pf"){
        return "float";
    }else if(result == "Pl"){
        return "long";
    }else{
        return "unknown";
    }
}

/**
 * This method parses the garbage collector list and generates a JSON file with the Content of the list.
 */

void GarbageCollector::generateJSON() {

    std::cout << "\n\n\n ************************** \n\n\n";

    Json::StyledStreamWriter writer;
    Json::Value my_list;

    Json::Value vec(Json::arrayValue);


    for(int i=0; i< listGc.getSize(); i++){
        VSPrtInfo* current = listGc.getByIndex(i);

        Json::Value obj;

        std::ostringstream get_addr;
        get_addr << current->getInstance();
        std::cout << get_addr.str() << "\n";

        obj["id"] = current->id;
        obj["addr"] = get_addr.str();
        obj["type"] = getType(current->getInstance());
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
