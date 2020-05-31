//
// Created by sebasmora on 30/5/20.
//
#include "../Server/ServerSocket.h"

int main(){

    ServerSocket& socket = *(new ServerSocket);
    socket.createSocket();
    return 0;
}