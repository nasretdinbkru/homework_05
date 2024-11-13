cmake_minimum_required(VERSION 3.28)
project(statistics)

set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_FLAGS "-O0")
SET(CMAKE_C_FLAGS "-O0")

add_executable(statistics statistics.cpp)
