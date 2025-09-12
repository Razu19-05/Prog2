cmake_minimum_required(VERSION 4.0)
project(CarpetaFuente)

set(CMAKE_CXX_STANDARD 20)

add_executable(CarpetaFuente main.cpp
        src/Utils.hpp
        src/Overloads.cpp
        src/Overloads.hpp)
