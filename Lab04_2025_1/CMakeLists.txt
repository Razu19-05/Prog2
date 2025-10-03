cmake_minimum_required(VERSION 4.0)
project(Lab04_2025_1)

set(CMAKE_CXX_STANDARD 26)

add_executable(Lab04_2025_1 main.cpp
        src/Utils.hpp
        src/BibliotecaGenerica.cpp
        src/BibliotecaGenerica.hpp
        src/BibliotecaEnteros.cpp
        src/BibliotecaEnteros.hpp
        src/BibliotecaRegistro.cpp
        src/BibliotecaRegistro.hpp)
