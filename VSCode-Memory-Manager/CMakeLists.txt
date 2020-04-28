cmake_minimum_required(VERSION 3.16)
project(VSCode_Memory_Manager)

set(CMAKE_CXX_FLAGS "-pthread")
set(CMAKE_CXX_STANDARD 17)

find_package(PkgConfig REQUIRED)
pkg_check_modules(JSONCPP jsoncpp)
link_libraries(${JSONCPP_LIBRARIES})
add_library(VSCode_Memory_Manager SHARED library.cpp library.h VSPointer.h GarbageCollector/GarbageCollector.h GarbageCollector/VSPtrInstance.h GarbageCollector/UUID.h List/ListGC.h)
target_link_libraries(VSCode_Memory_Manager ${JSONCPP_LIBRARIES})

