//
// Created by sebasmora on 8/5/20.
//

#include "remoteGarbageCollectorClient.h"



/**
* Increment remotely instance's ref count assign to the id
*/
void remoteGarbageCollectorClient::remoteIncrementInstance(std::string& id) {
    Json::Value root;
    root["COMMAND "] = "INCREMENT";
    root["id"] = id;
    //Send id
}



/**
 * Increment remotely instance's ref count assign to the id
 * @param id
 */
void remoteGarbageCollectorClient::remoteDecremetnInstance(std::string& id) {
    Json::Value root;
    root["COMMAND"] = "DECREMENT";
    root["id"] = id;
}


/**
 * Changes the value stored by VSPtr instance
 */
void remoteGarbageCollectorClient::changeValue() {


}
