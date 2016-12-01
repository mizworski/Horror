cmake_minimum_required(VERSION 3.5)
project(horror)

set(CMAKE_CXX_STANDARD 14)

SET (CMAKE_CXX_COMPILER "/usr/bin/clang++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -O2 -lstdc++ ")

set(SOURCE_FILES horror_example.cc smalltown.h monster.h citizen.h)
add_executable(horror ${SOURCE_FILES})
