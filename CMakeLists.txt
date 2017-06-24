cmake_minimum_required(VERSION 2.7)
project(set)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp set.h)
add_executable(set ${SOURCE_FILES})