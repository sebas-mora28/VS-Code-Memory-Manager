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
#include <openssl/md5.h>





/**
 * This class initialize the client socket and connect
 */
class ClientSocket {


private:
    unsigned int PORT = 54000;
    std::string ipAddres = "127.0.0.1";
    int client;
    int serverConnection;
    int messageSended;
    sockaddr_in hint;

public:

    ClientSocket();

    ~ClientSocket() = default; //Por definir



    /**
     * Creates client socket
     */
    void createSocket();

private:

    /**
     * Verifies if client socket created successfully
     * @return
     */
    bool isClientCreatedSuccessfully() const;



    /**
     * This method connects looking for the listen server and connect the client;
     */
    void connectClientToServer(std::string password);

    /**
     * Verifies if client socket is connected to the server
     * @return 
     */
    bool isClientConnectedToServer() const;


public:
    /**
     * This method send information to the server
     */
    std::string sendInfo(char* message);


    /**
     * Set PORT
     */
    void setPORT(int PORT);


    /**
     * Set IpAddress
     */
    void setIpAddress(std::string& ipAddress);


    std::string makeMD5(std::string message);



    /**
     * Set password
     */
    void setPassword(std::string& password);

private:

    /**
     * Verifies if the message was sended successfully
     * @return
     */
    bool messageSentSuccessfully() const;

    bool sendPassWord(std::string password);

    /**
     * Receives the info in bytes from the server and converts it into string
     * @return
     */
    std::string messageReceivedFromServer() const;
};


#endif //MEMORYMANAGER_CLIENTSOCKET_H
