#!bin/bash



rm -rf lib
mkdir lib

#Compile from .cpp to .o all the files needed for shared library
g++ -Wall -Wextra -std=c++17 -pedantic -o GarbageCollector.o -c -fPIC ../GarbageCollector/GarbageCollector.cpp -ljsoncpp
g++ -Wall -Wextra -std=c++17 -pedantic -o UUID.o -c -fPIC ../GarbageCollector/UUID/UUID.cpp
g++ -Wall -Wextra -std=c++17 -pedantic -o ClientSocket.o -c -fPIC ../Client/ClientSocket.cpp -ljsoncpp
g++ -Wall -Wextra -std=c++17 -pedantic -o RemoteMemory.o -c -fPIC ../Client/RemoteMemory.cpp -ljsoncpp


#Compile the shared library
g++ -shared -std=c++17 -o libVSCode.so GarbageCollector.o UUID.o ClientSocket.o RemoteMemory.o -ljsoncpp -lpthread


#Delete .o produced in the first step
rm GarbageCollector.o UUID.o RemoteMemory.o ClientSocket.o
#cp ../GarbageCollector/*.h ../Configuration/lib
#cp ../Client/*.h ../Configuration/lib
#cp ../VSPointer/*.h ../Configuration/lib
mv libVSCode.so ../Configuration/lib

#Copy and paste all the file needed for shared library
cp -r lib ~/Documents/TEC/Semestre\ III/Datos\ II/VS-Code-Memory-Manager/vsptr-memory-manager/
