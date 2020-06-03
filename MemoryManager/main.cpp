#include <iostream>
#include "VSPointer/VSPointer.h"
#include <thread>
#include "Client/ClientSocket.h"
#include <unordered_set>
#include "GarbageCollector/GarbageCollector.h"



#include "unordered_map"


int main() {

    while(true) {


        /*
        VSPtr<int> vsPtr = VSPtr<int>::NewRemote();
        VSPtr<int> vsPtr2 = VSPtr<int>::NewRemote();
        VSPtr<int> vsPtr3 = VSPtr<int>::NewRemote();
         */



        /*
        VSPtr<int> vsPtr2 = VSPtr<int>::New();
        *vsPtr2 = 65;

        VSPtr<int> vsPtr3 = VSPtr<int>::New();
        *vsPtr3 = 147;

        VSPtr<int> vsPtr4 = VSPtr<int>::New();
        *vsPtr4 = 145;
         * */

        std::this_thread::sleep_for(std::chrono::seconds(20));

    }
}
