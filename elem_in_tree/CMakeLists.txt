cmake_minimum_required(VERSION 3.6)
project(elem_tree)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

set(SOURCE_FILES main.cpp Tree.h)
add_executable(elem_tree ${SOURCE_FILES})
