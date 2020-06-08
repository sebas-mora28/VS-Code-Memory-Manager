#!bin/bash



rm -rf lib
mkdir lib

#Compile from .cpp to .o all the files needed for shared library
gcc -Wall -Wextra -o GarbageCollector.o -c -fPIC ../GarbageCollector/GarbageCollector.cpp -libstdc++
g++ -Wall -Wextra -o UUID.o -c -fPIC ../GarbageCollector/UUID/UUID.cpp
g++ -Wall -Wextra -o ClientSocket.o -c -fPIC ../Client/ClientSocket.cpp
g++ -Wall -Wextra -o RemoteMemory.o -c -fPIC ../Client/RemoteMemory.cpp
g++ -Wall -Wextra -o InializeClient.o -c -fPIC ../Client/InitializeClient.cpp




#Compile the shared library
g++ -shared -o libVSCode.so GarbageCollector.o UUID.o ClientSocket.o RemoteMemory.o InializeClient.o -ljsoncpp -lpthread
#g++ -shared -o libVSCodeRemote.so  -ljsoncpp

#Delete .o produced in the first step
rm GarbageCollector.o UUID.o RemoteMemory.o ClientSocket.o InializeClient.o

#cp ../GarbageCollector/*.h ../Configuration/lib
cp ../Client/*.h ../Configuration/lib
#cp ../VSPointer/*.h ../Configuration/lib
mv libVSCode.so ../Configuration/lib
#mv libVSCodeRemote.so ../Configuration/lib

#Copy and paste all the file needed for shared library
cp -r lib ~/Documents/TEC/Semestre\ III/Datos\ II/VS-Code-Memory-Manager/vsptr-memory-manager/
