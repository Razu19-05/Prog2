cmake_minimum_required(VERSION 4.0)
project(ClaseDePunteroAFuncion)

set(CMAKE_CXX_STANDARD 20)

add_executable(ClaseDePunteroAFuncion main.cpp
        src/Utils.hpp
        src/Funciones.cpp
        src/Funciones.hpp
        src/FuncionesGenericas.cpp
        src/FuncionesGenericas.hpp)
