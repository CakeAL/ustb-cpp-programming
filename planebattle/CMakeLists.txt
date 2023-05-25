cmake_minimum_required(VERSION 3.23)
project(planebattle)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(planebattle main.cpp
        MyPlane.cpp MyPlane.h
        ConsoleOperator.cpp ConsoleOperator.h
        EnemyPlane.cpp EnemyPlane.h
        TheMap.cpp TheMap.h
        Bullet.cpp Bullet.h)
