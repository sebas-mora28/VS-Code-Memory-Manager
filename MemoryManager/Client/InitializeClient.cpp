//
// Created by sebasmora on 31/5/20.
//
#include "InitializeClient.h"
#include "../Client/RemoteMemory.h"


extern "C" void  connectClient(char* port, char* ipAdress, char* password){
    const int PORT = atoi(port);
    std::string IPADDRESS(ipAdress);
    std::string PASSWORD(password);
    RemoteMemory::getInstance()->initClient(PORT, IPADDRESS, PASSWORD);
    std::cout << "SET CLIENT" << "\n";

}