cmake_minimum_required(VERSION 3.6)
project(mo)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

set(SOURCE_FILES ../max_tree/Tree.h main.cpp)
add_executable(mo ${SOURCE_FILES})
