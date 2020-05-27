//
// Created by sebasmora on 8/5/20.
//

#include "RemoteMemory.h"


RemoteMemory* RemoteMemory::instance = nullptr;


/**
* Increment remotely instance's ref count assign to the id
*/
void RemoteMemory::remoteIncrementInstance(std::string& id) {
    printf("INCREMENT REF COUNT REMOTELY");
    Json::Value root;
    root["COMMAND "] = "INCREMENT";
    root["id"] = id;
    sendMessage(root);
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
    sendMessage(root);
}




std::string RemoteMemory::sendMessage(Json::Value &root) {
    std::string message = root.toStyledString();
    std::string valueReceived = clientSocket.sendInfo(const_cast<char *>(message.c_str()));
    return valueReceived;

}

void *RemoteMemory::getAddr() {
    Json::Value root;
    root["command"] = "ADDR";
}

