#include <iostream>
#include "VSPointer/VSPointer.h"
#include <thread>
#include "Client/ClientSocket.h"
#include <unordered_set>
#include "Client/InitializeClient.h"

#include "unordered_map"


/*
class Base{

    std::string id;

    virtual void* get();

};

template<class T>
class Derivded : public Base {


public :
    Derivded(T& instance){
        this->instance = instance;
}
    void* get(){
        return instance;
    }

public:
    T instance;
};

*/

int main() {


    double* number = new double {};

    std::string name = "58.25";
    std::stringstream str(name);

    str >> *number;

    std::cout << *number << "\n";


    while(true) {



        VSPtr<int> vsptr = VSPtr<int>::NewRemote();
        *vsptr = 8;
        VSPtr<char> vsptr2 = VSPtr<char>::NewRemote();
        *vsptr2 = 'a';

        VSPtr<float> vsPtr4 = VSPtr<float>::NewRemote();
        vsPtr4 = 14.25f;

        VSPtr<double> vsPtr5 = VSPtr<double>::NewRemote();
        *vsPtr5 = 58.25;





        std::this_thread::sleep_for(std::chrono::seconds(10));

    }


}
