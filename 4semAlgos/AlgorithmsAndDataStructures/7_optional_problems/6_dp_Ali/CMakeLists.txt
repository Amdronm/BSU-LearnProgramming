cmake_minimum_required(VERSION 3.10.0)
project(Ali-Baba VERSION 0.1.0 LANGUAGES C CXX)

add_executable(Ali-Baba main.cpp)

target_compile_options(Ali-Baba PRIVATE "-std=c++23" "-O2")