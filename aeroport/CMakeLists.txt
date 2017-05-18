cmake_minimum_required(VERSION 3.6)
project(aeroport)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

set(SOURCE_FILES main.cpp Airport.cpp Airport.h Airctaft.cpp Airctaft.h)
add_executable(aeroport ${SOURCE_FILES})
