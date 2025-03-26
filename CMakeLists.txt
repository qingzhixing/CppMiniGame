cmake_minimum_required(VERSION 3.29)
project(CppMiniGame)

set(CMAKE_CXX_STANDARD 23)

add_executable(CppMiniGame main.cpp
        GameFrame/GameFrame.cpp
        GameFrame/GameFrame.h
        GuessNumber/GuessNumber.cpp
        GuessNumber/GuessNumber.h)

target_include_directories(CppMiniGame PUBLIC GameFrame GuessNumber)
