cmake_minimum_required(VERSION 3.20)
project(tp_project)
set(CMAKE_CXX_STANDARD 17)

include_directories(lib)

add_executable(exec
        lib/pacman.cpp
        play.cpp)