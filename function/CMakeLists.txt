cmake_minimum_required(VERSION 3.9)
project(function)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pthread")
add_executable(function main.cpp)