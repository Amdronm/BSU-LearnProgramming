cmake_minimum_required(VERSION 3.10.0)
project(brute_force VERSION 0.1.0 LANGUAGES C CXX)

add_executable(brute_force main.cpp)

target_compile_options(brute_force PRIVATE "-std=c++23")