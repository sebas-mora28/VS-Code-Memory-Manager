#include <iostream>
#include "VSPointer/VSPointer.h"
#include <thread>
#include "Client/ClientSocket.h"




class Persona{
    std::string name;
    int age;
    Persona* persona;

private:
    Persona(){
        age = 8;
        name = std::string("Persona");
    }

public:
    Persona* getInstance(){
        if(persona == nullptr){
            persona = new Persona();
            return persona;
        }
        return persona;
    }

    Persona* disableName(){
        delete persona;
        return this;
    }

};




int main() {


    ClientSocket clientSocket;

    clientSocket.createSocket();


    char* command = "ADD";
    std::cout << clientSocket.sendInfo(command) << "\n";
    //std::cout << clientSocket.sendInfo("SE ENVIO EL ID");


    /*
    while(true) {
        VSPtr<int> vsPtr = VSPtr<int>::New();
        *vsPtr = 8;

        VSPtr<int> vsPtr2 = VSPtr<int>::New();
        *vsPtr2 = 20;
        vsPtr2 = vsPtr;
        std::this_thread::sleep_for(std::chrono::seconds(5));


    }
     */

}