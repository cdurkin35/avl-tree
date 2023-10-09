cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(project1)
add_executable(project1 main.cpp Student.h Student.cpp Tree.h Tree.cpp)
