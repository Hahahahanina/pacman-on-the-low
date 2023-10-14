cmake_minimum_required(VERSION 3.20)
project(tp_project)
set(CMAKE_CXX_STANDARD 17)

include_directories(checkpoint_1/lib)

add_executable(exec
        checkpoint_1/lib/pacman.cpp
        checkpoint_1/lib/pacman.h
        checkpoint_1/play.cpp)
