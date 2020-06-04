//
// Created by sebasmora on 31/5/20.
//
#include "InitializeClient.h"
#include "../Client/RemoteMemory.h"


extern "C" void  testConnection(){
    RemoteMemory::getInstance()->testConnection();
}