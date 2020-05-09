//
// Created by sebasmora on 8/5/20.
//

#ifndef MEMORYMANAGER_CLIENTSOCKET_H
#define MEMORYMANAGER_CLIENTSOCKET_H

#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string>


class ClientSocket {


private:
    unsigned int PORT = 54000;
    std::string ipAddres = "127.0.0.1";
    int client;
    int serverConnection;
    int messageSended;
    sockaddr_in hint;

public:

    ClientSocket() = default; //Por definir

    ~ClientSocket() = default; //Por definir



    /**
     * Creates client socket
     */
    void createSocket();


    /**
     * Verify if client socket created successfully
     * @return
     */
    bool isClientCreatedSuccessfully() const;



    /**
     * This method connects looking for the listen server and connect the client;
     */
    void connetClientToServer();


    
    /**
     * Veify if client socket is connected to the server 
     * @return 
     */
    bool isClientConnectedToServer() const;
    
    
    void sendInfo();
    
    bool messageSendedSuccessfully() const;


    std::string messageReceivedFromServer();
};


#endif //MEMORYMANAGER_CLIENTSOCKET_H
