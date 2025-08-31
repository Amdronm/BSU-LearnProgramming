cmake_minimum_required(VERSION 3.10.0)
project(approximate VERSION 0.1.0 LANGUAGES C CXX)

add_executable(approximate simple_solution.cpp)

target_compile_options(approximate PRIVATE "-std=c++23")