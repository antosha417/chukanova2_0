cmake_minimum_required(VERSION 3.6)
project(list)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp list.cpp list.h Node.cpp Node.h)
add_executable(list ${SOURCE_FILES})