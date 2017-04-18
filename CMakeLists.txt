cmake_minimum_required(VERSION 3.6)
project(chukanova2_0)

add_subdirectory("k-d_tree")
add_subdirectory("max_tree")
add_subdirectory("vector")
add_subdirectory("list")
add_subdirectory("list_2")
set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp list/main.cpp)
add_executable(chukanova2_0 ${SOURCE_FILES})