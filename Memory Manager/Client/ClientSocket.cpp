//
// Created by sebasmora on 8/5/20.
//

#include <cstring>
#include "ClientSocket.h"

void ClientSocket::createSocket(){
    ClientSocket::client = socket(AF_INET, SOCK_STREAM, 0);

    try {
        if (!isClientCreatedSuccessfully()) {
            throw std::exception();
        }

        connetClientToServer();
    } catch (std::exception& err) {
        err.what();
    }
}


bool ClientSocket::isClientCreatedSuccessfully() const {
        return client != -1;
}


void ClientSocket::connetClientToServer() {
    hint.sin_family = AF_INET;
    hint.sin_port = htons(PORT);
    inet_pton(AF_INET, ipAddres.c_str(), &hint.sin_addr);

        serverConnection = connect(client, (sockaddr *) &hint, sizeof(hint));

        if(isClientConnectedToServer()){
            throw std::exception();
        }
        std::cout << "Client connected Successfully";
}



bool ClientSocket::isClientConnectedToServer() const {
    return serverConnection != -1;;
}

void ClientSocket::sendInfo() {

    std::string temp = "Hello";
    // variable temp
    int sendRes = send(client, temp.c_str(), temp.size() +1, 0);


    try {
        if (!messageSendedSuccessfully()) {
            throw std::exception();
        }
        printf("Mensage %s", messageReceivedFromServer().c_str());


    } catch (std::exception& err) {
        err.what();

    }



}

bool ClientSocket::messageSendedSuccessfully() const {
    return messageSended != -1;
}


std::string ClientSocket::messageReceivedFromServer() {

    char bufferReceived[1024];
    memset(bufferReceived, 0, 1024);

    int bytesReceived = recv(client, bufferReceived, 1024, 0);
    return std::string(bufferReceived, bytesReceived);



}
