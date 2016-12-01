cmake_minimum_required(VERSION 3.5)
project(horror)

set(CMAKE_CXX_STANDARD 14)

SET (CMAKE_CXX_COMPILER "/usr/bin/clang++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -O2 -lstdc++ ")

set(SOURCE_FILES smalltown.h monster.h citizen.h private/testing.cc private/testing.h)

add_executable(horror ${SOURCE_FILES} private/horror_example.cc)
add_executable(smalltown_test ${SOURCE_FILES} private/smalltown_test.cc)
add_executable(monster_test ${SOURCE_FILES} private/monsterTest.cc)
add_executable(citizen_test ${SOURCE_FILES} private/citizen_test.cc)