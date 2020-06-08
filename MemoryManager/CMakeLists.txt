cmake_minimum_required(VERSION 3.16)
project(MemoryManager)

set(CMAKE_CXX_FLAGS "-pthread -ljsoncpp")

set(CMAKE_CXX_STANDARD 17)

find_package(PkgConfig REQUIRED)
pkg_check_modules(JSONCPP jsoncpp)
link_libraries(${JSONCPP_LIBRARIES})
add_executable(MemoryManager main.cpp GarbageCollector/GarbageCollector.cpp GarbageCollector/GarbageCollector.h GarbageCollector/VSPtrInstance.h
        GarbageCollector/UUID/UUID.cpp GarbageCollector/UUID/UUID.h Client/ClientSocket.cpp Client/ClientSocket.h Client/RemoteMemory.cpp
        Client/RemoteMemory.h Server/ServerSocket.cpp Server/ServerSocket.h Client/InitializeClient.h Client/InitializeClient.cpp)
target_link_libraries(MemoryManager ${JSONCPP_LIBRARIES})

