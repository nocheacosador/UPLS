cmake_minimum_required(VERSION 3.2)

project(naqueue)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -O3")

add_executable(test test.cpp)

install(TARGETS test DESTINATION bin)