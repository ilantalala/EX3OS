cmake_minimum_required(VERSION 3.24)
project(EX3OS C)

set(CMAKE_C_STANDARD 99)

add_executable(EX3OS main.c BoundedQueue.c)
