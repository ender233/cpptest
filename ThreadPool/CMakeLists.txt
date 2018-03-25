cmake_minimum_required(VERSION 3.5)
project(ThreadPool)

set(Boost_USE_STATIC_LIBS ON)
find_package(Boost 1.63.0 COMPONENTS log thread system regex REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pthread")

add_executable(ThreadPool main.cpp ThreadPool.hpp)
target_link_libraries (ThreadPool ${Boost_LIBRARIES})
