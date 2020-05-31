//
// Created by sebasmora on 8/5/20.
//

#ifndef MEMORYMANAGER_REMOTEMEMORY_H
#define MEMORYMANAGER_REMOTEMEMORY_H

#include "ClientSocket.h"
#include <jsoncpp/json/json.h>



/**
 * This class i
 */
class RemoteMemory {

private:
    ClientSocket clientSocket;
    static RemoteMemory* instance;

    RemoteMemory(){
    };



public:


    static RemoteMemory* getInstance(){
        if(instance == nullptr){
            instance = new RemoteMemory();
            return instance;
        }
        return instance;

    }




    /**
     * Adds VSPtr instance remotely
     */


    void remoteAddInstance(std::string& type, std::string& id);


    /**
     * Increment remotely instance's ref count assign to the id
     */
    void remoteIncrementInstance(std::string& id);



    /**
     * Increment remotely instance's ref count assign to the id
     * @param id
     */
    void remoteDecremetnInstance(std::string& id);



    /**
     * Changes the value stored by the VSPtr instance
     */
    template<typename T>
    void changeValue(T& newValue, std::string& id);



    /**
     * Gets the value stored in VSPtr instance
     */
    template<typename T>
     T getValue(std::string& id);



    /**
     * Send Json to the server
     * @param root
     * @return
     */
     std::string sendMessage(Json::Value& root);



     /**
      * Converts value received from the server to the dataType of the VSptr
      */
     template<typename T>
     T convertValue(std::string& value);



     void getAddr();


};






/*
* Changes the value stored by VSPtr instance
*/
template<typename T>
void RemoteMemory::changeValue(T& newValue, std::string& id) {
    printf("CHANGE VALUE REMOTELY");
    Json::Value root;
    root["COMMAND"] = "CHANGE";
    root["id"] = id;
    root["value"] = newValue;
}


/**
 * Gets the value stored in VSptr instance
 * @param id
 */
template<typename T>
T RemoteMemory::getValue(std::string &id) {
    Json::Value root;
    root["COMMAND"] = "GET";
    root["id"] = id;
    std::string value = "8";//sendMessage(root);
    return convertValue<T>(value);
}


typedef std::string string;

template<typename T>
T RemoteMemory::convertValue(std::string& value){
    try {
        if (typeid(T) == typeid(int)) {
            return std::atoi(value.c_str());
        }
        if (typeid(T) == typeid(float)) {
            return std::stof(value.c_str());
        }
        if (typeid(T) == typeid(double)) {
            return std::stof(value.c_str());
        }
        if (typeid(T) == typeid(long)) {
            return std::stol(value.c_str());
        }
        if (typeid(T) == typeid(bool)) {
            return std::atoi(value.c_str());
        }
        if (typeid(T) == typeid(char)) {
            return *value.c_str();
        }
    } catch (std::exception& err) {
        printf("TYPE UNSUPPORTED");
    }





}



#endif //MEMORYMANAGER_REMOTEMEMORY_H
