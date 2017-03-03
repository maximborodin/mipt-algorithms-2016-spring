cmake_minimum_required(VERSION 3.5)
project(lcs)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp trivialAlgorithm.h advancedAlgorithm.h)
add_executable(lcs ${SOURCE_FILES})