//
// Created by sebasmora on 8/5/20.
//

#include <sstream>
#include "RemoteMemory.h"


RemoteMemory* RemoteMemory::instance = nullptr;


/**
* Increment remotely instance's ref count assign to the id
*/
void RemoteMemory::remoteIncrementInstance(std::string& id) {
    printf("INCREMENT REF COUNT REMOTELY");
    Json::Value root;
    root["COMMAND"] = "INCREMENT";
    root["id"] = id;
    post(root);
}



/**
 * Increment remotely instance's ref count assign to the id
 * @param id
 */
void RemoteMemory::remoteDecremetnInstance(std::string& id) {
    printf("DECREMENT REF COUNT REMOTELY");
    Json::Value root;
    root["COMMAND"] = "DECREMENT";
    root["id"] = id;
    post(root);
}





/**
 * Send information to server socket
 * @param root
 * @return
 */
std::string RemoteMemory::post(Json::Value &root) {
    std::string message = root.toStyledString();
    std::string valueReceived = clientSocket.sendInfo(const_cast<char *>(message.c_str()));
    return valueReceived;

}


/**
 * Add a VSPointer instance remotely
 * @param type type of VSPointer instance
 * @param id id of VSPointer instance
 */
void RemoteMemory::remoteAddInstance(const char* type, std::string& id) {
    printf("NEW REMOTE INSTANCE");
    Json::Value root;
    root["COMMAND"] = "ADD";
    Json::Value info;
    info["id"] = id;
    info["type"] = type;
    root["VSPtrInfo"] = info;
    post(root);

}


/**
 * Gets the value stored in VSptr instance
 * @param id
 */
std::string RemoteMemory::getValue(std::string &id) {
    Json::Value root;
    root["COMMAND"] = "GET";
    root["id"] = id;
    std::string value = post(root);
    return value;
}




