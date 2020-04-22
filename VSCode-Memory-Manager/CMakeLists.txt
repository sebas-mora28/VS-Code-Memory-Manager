cmake_minimum_required(VERSION 3.16)
project(VSCode_Memory_Manager)

set(CMAKE_CXX_STANDARD 17)

add_library(VSCode_Memory_Manager SHARED library.cpp library.h VSPointer.h GarbageCollector/GarbageCollector.h GarbageCollector/VSPtrInstance.h GarbageCollector/UUID.h List/ListGC.h)

