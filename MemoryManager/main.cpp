#include <iostream>
#include "VSPointer/VSPointer.h"
#include <thread>
#include "Client/ClientSocket.h"
#include <unordered_set>
#include "Server/ServerSocket.h"


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

    while(true) {


        VSPtr<int> vsptr = VSPtr<int>::New();
        //*vsptr = 254;

        VSPtr<double> vsPtr2 = VSPtr<double>::New();
        *vsPtr2 = 145.254;

        //VSPtr<char> vsPtr3 = VSPtr<char>::New();
        //*vsPtr2 = 'x';

        //VSPtr<float> vsPtr4 = VSPtr<float>::New();
        //*vsPtr4 = 145.254;





        /*
        VSPtr<int> vsptrR = VSPtr<int>::NewRemote();
        *vsptrR = 254;

        VSPtr<double> vsPtr2R = VSPtr<double>::NewRemote();
        *vsPtr2R = 145.254;

        VSPtr<char> vsPtr3R = VSPtr<char>::NewRemote();
        *vsPtr2R = 'x';

        VSPtr<float> vsPtr4R = VSPtr<float>::NewRemote();
        *vsPtr4R = 145.254;


        std::cout << "EL VALOR ES " << &vsPtr4 << "\n";
        std::cout << "EL VALOR ES " << &vsPtr2R << "\n";
        std::cout << "EL VALOR ES " << &vsPtr4R << "\n";

         */



        std::this_thread::sleep_for(std::chrono::seconds(10));

    }


}
