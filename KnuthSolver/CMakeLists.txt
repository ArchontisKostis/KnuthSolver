cmake_minimum_required(VERSION 3.26)
project(KnuthSolver C)

set(CMAKE_C_STANDARD 11)

add_executable(KnuthSolver main.c
        include/search.h
        include/search.c
        include/io.h
        include/io.c
        include/utils.h
        include/utils.c
)