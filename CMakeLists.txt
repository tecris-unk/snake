cmake_minimum_required(VERSION 3.29)
project(snake)

set(CMAKE_CXX_STANDARD 26)

add_executable(snake main.cpp
        functions.cpp
        functions.h
        class.h
)
