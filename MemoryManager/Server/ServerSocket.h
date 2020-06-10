//
// Created by david on 27/5/20.
//

#ifndef MEMORYMANAGER_SERVERSOCKET_H
#define MEMORYMANAGER_SERVERSOCKET_H


#include <iostream>
#include "jsoncpp/json/json.h"


class ServerSocket {


private:
    int currentSocket;
public:

    /**
     * Constructor
     */
    ServerSocket() = default;

    /**
     * Destructor
     */
    ~ServerSocket() = default;



    /**
    * Creates Server sockets
    */
    void createSocket();


    /**
    * Increment ref count of VSPointer instance
    * @param id id of VSPointer
    */
    void increment(std::string id);


    /**
    * Decrement ref count of VSPointer instance
    * @param id id of VSPointer
    */
    void decrement(std::string id);



    /**
    * Evaluate JSON received from client
    * @param info json received from client socket
    */
    void evaluateJson(Json::Value& info);

private:


    /**
    * Send information to client
    * @param clientServer client socket
    * @param buf buffered sended to client
    */

    static void sendMessage(int clientServer, std::string& buffer);


};


#endif //MEMORYMANAGER_SERVERSOCKET_H
