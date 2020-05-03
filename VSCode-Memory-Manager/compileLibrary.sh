#!bin/bas




#sed -i 's\'GarbageCollector.h'\'GarbageCollector.h/GarbageCollecotor.h'\g' VSPointer.h


g++ -Wall -Wextra -o GarbageCollector.o -c -fPIC GarbageCollector/GarbageCollector.cpp
g++ -Wall -Wextra -o UUID.o -c -fPIC GarbageCollector/UUID.cpp



g++ -shared -o libVSCode.so GarbageCollector.o UUID.o -ljsoncpp -lpthread


#sed -i 's\'GarbageCollector/GarbageCollector.h'\'GarbageCollector.h'\g' VSPointer.h
