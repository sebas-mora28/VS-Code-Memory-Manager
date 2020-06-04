#include <iostream>
#include "VSPointer/VSPointer.h"
#include <thread>
#include "Client/ClientSocket.h"
#include <unordered_set>
#include "Client/InitializeClient.h"



#include "unordered_map"


int main() {


    while(true) {


        VSPtr<int> vsPtr = VSPtr<int>::NewRemote();
        VSPtr<int> vsPtr2 = VSPtr<int>::NewRemote();
        VSPtr<int> vsPtr3 = VSPtr<int>::NewRemote();

        VSPtr<int> vsPtr22 = VSPtr<int>::New();
        *vsPtr22 = 65;

        VSPtr<int> vsPtr33 = VSPtr<int>::New();
        *vsPtr33 = 147;

        VSPtr<int> vsPtr4 = VSPtr<int>::New();
        *vsPtr4 = 145;

        VSPtr<char> vsPtr1 = VSPtr<char>::New();

        *vsPtr1 = 'c';

        std::this_thread::sleep_for(std::chrono::seconds(10));

    }
}
