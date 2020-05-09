//
// Created by sebasmora on 8/5/20.
//

#ifndef MEMORYMANAGER_REMOTEGARBAGECOLLECTORCLIENT_H
#define MEMORYMANAGER_REMOTEGARBAGECOLLECTORCLIENT_H

#include "ClientSocket.h"



/**
 * This class i
 */
class remoteGarbageCollectorClient {
    ClientSocket clientSocket;




    /**
     * Adds VSPtr instance remotely
     */
    void remoteAddInstance();


    /**
     * Increment remotely instance's ref count assign to the id
     */
    void remoteIncrementInstance(std::string& id);



    /**
     * Increment remotely instance's ref count assign to the id
     * @param id
     */
    void remoteDecremetnInstance(std::string& id);




};


#endif //MEMORYMANAGER_REMOTEGARBAGECOLLECTORCLIENT_H
