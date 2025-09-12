cmake_minimum_required(VERSION 4.0)
project(RepasandoMemoriaDinamica)

set(CMAKE_CXX_STANDARD 20)

add_executable(RepasandoMemoriaDinamica main.cpp
        src/Utils.hpp
        structs/Tweets.hpp
        src/HandleTweets.hpp
        src/HandleTweets.cpp)
