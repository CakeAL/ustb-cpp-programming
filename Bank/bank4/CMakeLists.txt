cmake_minimum_required(VERSION 3.21)
project(bank4)

set(CMAKE_CXX_STANDARD 14)

add_executable(bank4
        date.cpp date.h
        Account.cpp Account.h
        SavingsAccount.cpp SavingsAccount.h
        Accumulator.cpp Accumulator.h
        CreditAccount.cpp CreditAccount.h
        step_4.cpp)
