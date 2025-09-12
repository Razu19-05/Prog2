cmake_minimum_required(VERSION 4.0)
project(ClaseRepasoMemoria)

set(CMAKE_CXX_STANDARD 20)

add_executable(ClaseRepasoMemoria main.cpp
        src/Utils.hpp
        src/Functions.cpp
        src/Functions.hpp
)
