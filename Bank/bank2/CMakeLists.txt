cmake_minimum_required(VERSION 3.21)
project(bank2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(bank2
        account.cpp
        account.h
        date.cpp
        date.h
        step_2.cpp)
