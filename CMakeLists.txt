cmake_minimum_required(VERSION 3.25)
project(SecondSemester C)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

enable_testing()

add_compile_options(-Wall -Wextra -pedantic)

add_subdirectory(src)