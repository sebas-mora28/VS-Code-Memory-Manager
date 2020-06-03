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


void RemoteMemory::remoteAddInstance(std::string &type, std::string& id) {
    Json::Value root;
    root["COMMAND"] = "ADD";
    Json::Value info;
    info["type"] = type;
    info["id"] = id;
    root["VSPtrInfo"] = info;
    sendMessage(root);

}

void RemoteMemory::initClient(const int PORT, std::string &ipAddress, std::string &password) {
    clientSocket.setPORT(PORT);
    clientSocket.setIpAdrress(ipAddress);

}



