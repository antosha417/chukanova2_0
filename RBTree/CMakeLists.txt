cmake_minimum_required(VERSION 3.6)
project(RB)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

set(SOURCE_FILES main.cpp RBTree.h Queue.h)
add_executable(RB ${SOURCE_FILES})
