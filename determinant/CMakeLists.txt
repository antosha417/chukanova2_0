cmake_minimum_required(VERSION 3.6)
project(determinant)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

set(SOURCE_FILES main.cpp)
add_executable(determinant ${SOURCE_FILES})
