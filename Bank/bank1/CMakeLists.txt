cmake_minimum_required(VERSION 3.21)
project(bank1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(bank1
        account.cpp
        account.h
        step_1.cpp)
