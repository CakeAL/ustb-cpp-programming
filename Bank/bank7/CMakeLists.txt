cmake_minimum_required(VERSION 3.21)
project(bank7)

set(CMAKE_CXX_STANDARD 14)

add_executable(bank7
        date.cpp date.h
        Account.h Account.cpp
        SavingsAccount.cpp SavingsAccount.h
        Accumulator.cpp Accumulator.h
        CreditAccount.cpp CreditAccount.h
        step_7.cpp)
