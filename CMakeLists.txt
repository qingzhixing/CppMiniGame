cmake_minimum_required(VERSION 3.29)
project(CppMiniGame)

set(CMAKE_CXX_STANDARD 23)

add_executable(CppMiniGame main.cpp
        GameFrame/GameFrame.h
        GuessNumber/GuessNumber.cpp
        GuessNumber/GuessNumber.h
        GameFrame/GameFrame.cpp
        Snakes/Snakes.cpp
        Snakes/Snakes.h)

set(CMAKE_EXE_LINKER_FLAGS -static)

target_include_directories(CppMiniGame PUBLIC GameFrame GuessNumber)

