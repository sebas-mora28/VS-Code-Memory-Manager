//
// Created by sebasmora on 8/5/20.
//

#include "remoteGarbageCollectorClient.h"


/**
* Adds VSPtr instance remotely
*/
void remoteGarbageCollectorClient::remoteAddInstance() {

    //Send instance thought socket client

}

/**
* Increment remotely instance's ref count assign to the id
*/
void remoteGarbageCollectorClient::remoteIncrementInstance(std::string& id) {
    //Send id
}



/**
 * Increment remotely instance's ref count assign to the id
 * @param id
 */
void remoteGarbageCollectorClient::remoteDecremetnInstance(std::string& id) {

}
