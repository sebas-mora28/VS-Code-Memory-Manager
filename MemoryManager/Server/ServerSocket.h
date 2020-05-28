//
// Created by david on 27/5/20.
//

#ifndef MEMORYMANAGER_SERVERSOCKET_H
#define MEMORYMANAGER_SERVERSOCKET_H


#include <iostream>
#include "jsoncpp/json/json.h"


class ServerSocket {
public:
    ServerSocket() = default;

    ~ServerSocket() = default;

    int createSocket();

    void increment(std::string id);

    void decrement(std::string id);

private:

    static void sendMessage(int clientServer, char buf[4096]);


};


#endif //MEMORYMANAGER_SERVERSOCKET_H
