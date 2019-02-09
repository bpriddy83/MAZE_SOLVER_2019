cmake_minimum_required(VERSION 3.12)
project(project2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(project2
        CMakeLists.txt
        main.cpp
        maze_solver.cpp
        maze_solver.h)
