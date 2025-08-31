cmake_minimum_required(VERSION 3.10.0)
project(max_flow VERSION 0.1.0 LANGUAGES C CXX)

add_executable(max_flow main.cpp)

target_compile_options(max_flow PRIVATE "-std=c++23")