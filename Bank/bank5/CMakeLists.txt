cmake_minimum_required(VERSION 3.21)
project(bank5)

set(CMAKE_CXX_STANDARD 14)

add_executable(bank5
        date.cpp date.h
        Account.h Account.cpp
        SavingsAccount.cpp SavingsAccount.h
        Accumulator.cpp Accumulator.h
        CreditAccount.cpp CreditAccount.h
        step_5.cpp)
