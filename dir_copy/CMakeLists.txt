cmake_minimum_required(VERSION 3.6)
project(copy_dir)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

set(SOURCE_FILES main.cpp Tree.h)
add_executable(copy_dir ${SOURCE_FILES})
