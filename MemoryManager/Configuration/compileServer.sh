#!/usr/bin/env bash




g++ -Wall -Wextra  -o GarbageCollector.o -c ../GarbageCollector/GarbageCollector.cpp
g++ -Wall -Wextra  -o UUID.o -c ../GarbageCollector/UUID/UUID.cpp
g++ -Wall -Wextra  -o Server.o -c ../Server/ServerSocket.cpp


rm -rf serverCompiled
mkdir serverCompiled

mv GarbageCollector.o UUID.o Server.o serverCompiled

cd serverCompiled
g++ -Wall -Wextra  -o init.o -c ../initServer.cpp
g++ -o initServer GarbageCollector.o UUID.o Server.o init.o -ljsoncpp -lpthread -lcrypto

#initServer ~/Desktop/
#mv initServer ~/Desktop
mv initServer ~/Documents/TEC/Semestre\ III/Datos\ II/VS-Code-Memory-Manager/vsptr-memory-manager/src

