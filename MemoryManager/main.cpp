#include <iostream>
#include "VSPointer/VSPointer.h"
#include <thread>
#include "Client/ClientSocket.h"
#include <unordered_set>
#include "Server/ServerSocket.h"


#include "unordered_map"


int main() {



    while(true) {


        VSPtr<int> vsptr = VSPtr<int>::New();
        *vsptr = 845;

        VSPtr<char> vsPtr3 = VSPtr<char>::New();
        *vsPtr3 = 'x';

        //VSPtr<float> vsPtr4 = VSPtr<float>::New();
        //*vsPtr4 = 145.254;



        /*
        VSPtr<int> vsptrR = VSPtr<int>::NewRemote();
        *vsptrR = 145;

        vsptr = vsptrR;

        *vsptr = 45;
         * */


        std::cout << "EL VALOR ES : " << &vsPtr3<< "\n";
        /*
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
