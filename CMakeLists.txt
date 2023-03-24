cmake_minimum_required(VERSION 3.14)
project(TP2)

set(CMAKE_CXX_STANDARD 11)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

FetchContent_MakeAvailable(googletest)

add_executable(TP2 Graphe.cpp Principal.cpp ReseauAerien.cpp)

enable_testing()

add_subdirectory(TP2_Tests)

