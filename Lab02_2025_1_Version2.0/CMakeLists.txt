cmake_minimum_required(VERSION 4.0)
project(Lab02_2025_1_Version2_0)

set(CMAKE_CXX_STANDARD 20)

add_executable(Lab02_2025_1_Version2_0 main.cpp
        src/Utils.hpp
        struct/Structs.hpp
        src/Overloads.cpp
        src/Overloads.hpp
        src/Functions.cpp
        src/Functions.hpp)
