//
// Created by sebasmora on 8/5/20.
//

#include <cstring>
#include <fstream>
#include <jsoncpp/json/json.h>
#include <iomanip>
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
        //Acá tiene que pasarle a connectClientToServer la contraseña que se agarra del input.
        connectClientToServer();
    } catch (std::exception& err) {
        std::cout << "Error creating client  : " << err.what() << "\n";
    }
}

bool ClientSocket::sendPassWord(std::string password) {
    std::string s = makeMD5(password);

}


std::string ClientSocket::makeMD5(std::string message) {

    unsigned char result[MD5_DIGEST_LENGTH];
    MD5((unsigned char*)message.c_str(), message.size(), result);

    std::ostringstream sout;
    sout<<std::hex<<std::setfill('0');
    for(long long c: result)
    {
        sout<<std::setw(2)<<(long long)c;
    }
    return sout.str();
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
void ClientSocket::connectClientToServer()  {
    hint.sin_family = AF_INET;
    hint.sin_port = htons(PORT);
    try {
        inet_pton(AF_INET, ipAddres.c_str(), &hint.sin_addr);

        serverConnection = connect(client, (sockaddr *) &hint, sizeof(hint));

        char bufferReceived[1024];
        memset(bufferReceived, 0, 1024);
        int bytesReceived = recv(client, bufferReceived, 1024, 0);
        std::string message = std::string(bufferReceived, bytesReceived);

        if (!isClientConnectedToServer() and (message == makeMD5(password))) {
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
    createSocket();
    messageSended = send(client, message, strlen(message) + 1, 0);
    try {
        if (!messageSentSuccessfully()) {
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
bool ClientSocket::messageSentSuccessfully() const {
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
        close(client);
        return std::string(bufferReceived, bytesReceived);

    } catch (std::exception& err) {
        std::cout << "Error receiving message : " << err.what() << "\n";

    }

}


 void ClientSocket::setPORT(int PORT) {
    this->PORT = PORT;
}

void ClientSocket::setIpAddress(std::string &ipAddress) {
    this->ipAddres = ipAddress;

}

void ClientSocket::setPassword(std::string &) {
    //Set password

}


/**
 * Client Socket constructor
 */
ClientSocket::ClientSocket() {
    /*
        std::ifstream connectionInfo;
        std::string data;
        connectionInfo.open("./lib/connectionData.json");
        Json::Reader reader;
        Json::Value obj;
        reader.parse(connectionInfo, obj);
        this->PORT =  obj["ConnectionInfo"]["PORT"].asInt();
        this->ipAddres = obj["ConnectionInfo"]["IpAdress"].toStyledString();
        this->password = obj["ConnectionInfo"]["password"].toStyledString();
        */
}


