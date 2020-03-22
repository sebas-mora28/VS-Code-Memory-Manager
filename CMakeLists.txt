cmake_minimum_required(VERSION 3.15)
project(VS_Code_Memory_Manager)

set(CMAKE_CXX_STANDARD 14)

add_library(VS_Code_Memory_Manager SHARED library.cpp library.h VSPtr.h)