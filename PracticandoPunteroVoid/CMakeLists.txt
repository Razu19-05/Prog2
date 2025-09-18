cmake_minimum_required(VERSION 4.0)
project(PracticandoPunteroVoid)

set(CMAKE_CXX_STANDARD 20)

add_executable(PracticandoPunteroVoid main.cpp
        src/Utils.hpp
        src/FuncionesGenericas.cpp
        src/FuncionesGenericas.hpp
        src/Structs.hpp)
