cmake_minimum_required(VERSION 3.20)

project(Pacman)

add_executable(exec play.cpp)
add_subdirectory(lib)
target_link_libraries(exec PUBLIC lib)
target_include_directories(exec PUBLIC lib)