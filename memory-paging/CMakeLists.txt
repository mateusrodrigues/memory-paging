cmake_minimum_required(VERSION 3.14)
project(memory_paging)

set(CMAKE_CXX_STANDARD 14)

add_executable(memory_paging main.cpp Page.cpp Page.h)
