#!bin/bash






g++ -Wall -Wextra -o GarbageCollector.o -c -fPIC GarbageCollector/GarbageCollector.cpp
g++ -Wall -Wextra -o UUID.o -c -fPIC GarbageCollector/UUID.cpp



g++ -shared -o libVSCode.so GarbageCollector.o UUID.o -ljsoncpp -lpthread

rm -rf GarbageCollecotor.o UUID.o


