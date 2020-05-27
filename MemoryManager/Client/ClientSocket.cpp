//
// Created by sebasmora on 8/5/20.
//

#include <cstring>
#include "ClientSocket.h"



/**
* Creates client socket
*/
void ClientSocket::createSocket(){

    try {
        ClientSocket::client = socket(AF_INET, SOCK_STREAM, 0);

        if (!isClientCreatedSuccessfully()) {
            throw std::exception();
        }
        connetClientToServer();
    } catch (std::exception& err) {
        std::cout << "Error creating client  : " << err.what() << "\n";
    }
}


/**
 *Verifies if client socket created successfully
 * @return
 */
bool ClientSocket::isClientCreatedSuccessfully() const {
        return client != -1;
}



/**
 * This method connects looking for the listen server and connect the client;
 */
void ClientSocket::connetClientToServer()  {
    hint.sin_family = AF_INET;
    hint.sin_port = htons(PORT);
    try {
        inet_pton(AF_INET, ipAddres.c_str(), &hint.sin_addr);

        serverConnection = connect(client, (sockaddr *) &hint, sizeof(hint));


        if (!isClientConnectedToServer()) {
            throw std::exception();
        }
        std::cout << "Client connected Successfully";

    } catch (std::exception& err) {
        std::cout << "Error conectando el socket" << "\n";

    }
}


/**
* Verifies if client socket is connected to the server
* @return
*/
bool ClientSocket::isClientConnectedToServer() const {
    return serverConnection  != -1;
}



/**
 * This method send information to the server
 */
std::string  ClientSocket::sendInfo(char* message) {
    messageSended = send(client, message, strlen(message) + 1, 0);
    try {
        if (!messageSendedSuccessfully()) {
            throw std::exception();
        }
        return messageReceivedFromServer();
    } catch (std::exception& err) {
        std::cout << "Error sendInfo : ";


    }


}



/**
 * Verifies if the message was sended successfully
 * @return
 */
bool ClientSocket::messageSendedSuccessfully() const {
    return messageSended != -1;
}



/**
 * Receives the info in bytes from the server and converts it into string
 * @return
 */
std::string ClientSocket::messageReceivedFromServer() const {
    try {
        char bufferReceived[1024];
        memset(bufferReceived, 0, 1024);
        int bytesReceived = recv(client, bufferReceived, 1024, 0);
        return std::string(bufferReceived, bytesReceived);

    } catch (std::exception& err) {
        std::cout << "Error receiving message : " << err.what() << "\n";

    }

}
