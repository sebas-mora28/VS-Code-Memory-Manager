#include <iostream>
#include "VSPointer.h"
#include <thread>
#include "Client/ClientSocket.h"
const char* name(){
    std::string name = "sebas";
    return name.c_str();
}


template<typename T>
void foo(int& num){
    std::cout << num << "    "  << &num << "\n";
}




int main() {



    while(true) {
        VSPtr<int> vsPtr = VSPtr<int>::New();
        *vsPtr = 8;

        VSPtr<int> vsPtr2 = VSPtr<int>::New();
        *vsPtr2 = 20;
        vsPtr2 = vsPtr;
        std::this_thread::sleep_for(std::chrono::seconds(5));


    }






}
