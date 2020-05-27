//
// Created by sebasmora on 8/5/20.
//

#ifndef MEMORYMANAGER_REMOTEGARBAGECOLLECTORCLIENT_H
#define MEMORYMANAGER_REMOTEGARBAGECOLLECTORCLIENT_H

#include "ClientSocket.h"
#include <jsoncpp/json/json.h>



/**
 * This class i
 */
class remoteGarbageCollectorClient {
    ClientSocket clientSocket;


public:

    /**
     * Adds VSPtr instance remotely
     */

    template<typename T>
    void remoteAddInstance(T value, std::string& type,  std::string& id);


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
    void changeValue();




};







/**
* Adds VSPtr instance remotely
*/
template<typename T>
void remoteGarbageCollectorClient::remoteAddInstance(T value, std::string& type, std::string& id) {
    Json::Value root;
    root["COMMAND"] = "ADD";

    Json::Value info;
    info["id"] = id;
    info["value"] = value;
    info["type"] = type;
    root["VSPtrInfo"] = info;

}



#endif //MEMORYMANAGER_REMOTEGARBAGECOLLECTORCLIENT_H
