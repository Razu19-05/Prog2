cmake_minimum_required(VERSION 4.0)
project(Lab05_2025_2)

set(CMAKE_CXX_STANDARD 26)

add_executable(Lab05_2025_2 main.cpp
        src/Utils.hpp
        src/BibliotecaGenerica.cpp
        src/BibliotecaGenerica.hpp
        src/BibliotecaConductores.cpp
        src/BibliotecaConductores.hpp
        src/BibliotecaInfracciones.cpp
        src/BibliotecaInfracciones.hpp)
