#include <iostream>
#include "VSPointer.h"
#include <thread>


int main() {

    while(true) {
        VSPtr<int> vsPtr = VSPtr<int>::New();
        *vsPtr = 8;

        std::this_thread::sleep_for(std::chrono::seconds(5));


    }




}
