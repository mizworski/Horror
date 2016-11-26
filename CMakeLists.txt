cmake_minimum_required(VERSION 3.6)
project(horror)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES horror_example.cc smalltown.cc smalltown.h monster.cc monster.h citizen.cc citizen.h)
add_executable(horror ${SOURCE_FILES})