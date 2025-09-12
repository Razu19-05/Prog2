cmake_minimum_required(VERSION 4.0)
project(RepasandoMemoriaExacta)

set(CMAKE_CXX_STANDARD 20)

add_library(src STATIC src/Functions.cpp)
add_executable(RepasandoMemoriaExacta main.cpp
        src/Utils.hpp
        src/Functions.cpp
        src/Functions.hpp
        src/HandleTweets.cpp
        src/HandleTweets.hpp
        structs/Structs.hpp)

target_link_libraries(RepasandoMemoriaExacta src)