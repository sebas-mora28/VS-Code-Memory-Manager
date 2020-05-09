#!bin/bash






#Compile from .cpp to .o all the files needed for shared library
g++ -Wall -Wextra -o GarbageCollector.o -c -fPIC GarbageCollector/GarbageCollector.cpp
g++ -Wall -Wextra -o UUID.o -c -fPIC GarbageCollector/UUID.cpp


#Compile the shared library
g++ -shared -o libVSCode.so GarbageCollector.o UUID.o -ljsoncpp -lpthread


#Delete .o produced in the first step
rm GarbageCollector.o UUID.o


#Copy and paste all the file needed for shared library
cp GarbageCollector/*.h VSPointer.h libVSCode.so ~/Documents/TEC/Semestre\ III/Datos\ II/VS-Code-Memory-Manager/vsptr-memory-manager/lib/


#Delete libVSCode.so
rm libVSCode.so
